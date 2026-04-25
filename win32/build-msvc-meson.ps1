param(
    [Parameter(Mandatory)] [String] $VSVersion,
    [Parameter(Mandatory)] [String] $Platform,
    [Parameter(Mandatory)] [String] $Configuration,
    [String] $PythonPath = "",
    [String] $PlatformToolset = "",
    [Switch] $Clean
)

$ErrorActionPreference = "Stop"

function Resolve-Python {
    param([String] $Path)

    if ($Path -and (Test-Path (Join-Path $Path "python.exe"))) {
        return (Join-Path $Path "python.exe")
    }

    $python = Get-Command python -ErrorAction SilentlyContinue
    if ($python) {
        return $python.Source
    }

    $py = Get-Command py -ErrorAction SilentlyContinue
    if ($py) {
        return $py.Source
    }

    throw "Python was not found"
}

function Resolve-VsInstall {
    param([String] $Version)

    $versionRange = switch ($Version) {
        "16" { "[16.0,17.0)" }
        "17" { "[17.0,18.0)" }
        default { throw "Unsupported Visual Studio version $Version" }
    }

    $vswhere = $null
    $programFilesX86 = ${env:ProgramFiles(x86)}
    if ($programFilesX86) {
        $candidate = Join-Path $programFilesX86 "Microsoft Visual Studio\Installer\vswhere.exe"
        if (Test-Path $candidate) {
            $vswhere = $candidate
        }
    }

    if (-not $vswhere) {
        $vswhereCommand = Get-Command vswhere -ErrorAction SilentlyContinue
        if ($vswhereCommand) {
            $vswhere = $vswhereCommand.Source
        }
    }

    if (-not $vswhere) {
        throw "vswhere was not found"
    }

    $install = & $vswhere -latest -version $versionRange -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if ($install) {
        return $install.Trim()
    }

    $install = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if ($install) {
        return $install.Trim()
    }

    throw "Visual Studio with C++ tools was not found"
}

function Resolve-VcVarsVersion {
    param(
        [String] $VsInstall,
        [String] $Toolset
    )

    $prefix = switch ($Toolset) {
        "v141" { "14.1" }
        "v142" { "14.2" }
        default { "" }
    }

    if (-not $prefix) {
        return ""
    }

    $toolsDir = Join-Path $VsInstall "VC\Tools\MSVC"
    $tool = Get-ChildItem $toolsDir -Directory |
        Where-Object { $_.Name.StartsWith($prefix) } |
        Sort-Object Name -Descending |
        Select-Object -First 1

    if (-not $tool) {
        throw "MSVC toolset $Toolset was not found under $toolsDir"
    }

    $parts = $tool.Name.Split(".")
    if ($parts.Count -lt 2) {
        throw "Could not parse MSVC toolset version $($tool.Name)"
    }

    return "$($parts[0]).$($parts[1])"
}

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$python = Resolve-Python $PythonPath
$pythonDir = Split-Path -Parent $python
$pythonUserScripts = (& $python -c "import site; print(site.USER_BASE + r'\Scripts')").Trim()
if (-not $pythonUserScripts) {
    throw "Could not determine Python user scripts directory"
}

$vsInstall = Resolve-VsInstall $VSVersion
$vcvars = Join-Path $vsInstall "VC\Auxiliary\Build\vcvarsall.bat"
if (-not (Test-Path $vcvars)) {
    throw "vcvarsall.bat was not found at $vcvars"
}

$vcArch = switch ($Platform) {
    "Win32" { "x86" }
    "x64" { "amd64" }
    "ARM64" { "amd64_arm64" }
    default { throw "Unsupported platform $Platform" }
}

$toolsetVersion = Resolve-VcVarsVersion -VsInstall $vsInstall -Toolset $PlatformToolset
$optimization = if ($Configuration.StartsWith("Debug")) { "0" } else { "3" }
$vsCrt = if ($Configuration.StartsWith("Debug")) { "mdd" } else { "md" }
$glibDebug = if ($Configuration.StartsWith("Debug")) { "enabled" } else { "disabled" }

$workspaceRoot = Split-Path -Parent $repoRoot
$depsRoot = Join-Path $workspaceRoot "deps"
$useWinlibDeps = (Test-Path (Join-Path $depsRoot "include")) -and (Test-Path (Join-Path $depsRoot "lib"))
$useLegacyDllNames = $true

$buildDir = Join-Path $repoRoot "_build-vs$VSVersion-$Platform-$Configuration"
$prefix = Join-Path $workspaceRoot "vs$VSVersion\$Platform"

if ($Clean) {
    if (Test-Path $buildDir) {
        Remove-Item -Recurse -Force $buildDir
    }
    if (Test-Path $prefix) {
        Remove-Item -Recurse -Force $prefix
    }
    return
}

$cmdFile = Join-Path ([System.IO.Path]::GetTempPath()) ("glib-meson-build-{0}-{1}-{2}.cmd" -f $VSVersion, $Platform, $Configuration)
$vcVarsArgs = "`"$vcvars`" $vcArch"
if ($toolsetVersion) {
    $vcVarsArgs += " -vcvars_ver=$toolsetVersion"
}

$setupMode = if (Test-Path (Join-Path $buildDir "meson-private\coredata.dat")) { "--reconfigure" } else { "" }
$mesonOptions = @(
    "setup",
    $setupMode,
    "`"$buildDir`"",
    "`"$repoRoot`"",
    "--vsenv",
    "--prefix", "`"$prefix`"",
    "--bindir", "bin",
    "--libdir", "lib",
    "--includedir", "include",
    "--default-library", "shared",
    "-Doptimization=$optimization",
    "-Ddebug=true",
    "-Db_vscrt=$vsCrt",
    "-Dglib_debug=$glibDebug",
    "-Dwinlib_legacy_dll_names=$($useLegacyDllNames.ToString().ToLowerInvariant())",
    "-Dtests=false",
    "-Dinstalled_tests=false",
    "-Dintrospection=disabled",
    "-Ddocumentation=false",
    "-Dman-pages=disabled",
    "-Dsysprof=disabled",
    "-Dlibelf=disabled",
    "-Dfile_monitor_backend=win32",
    "-Dpcre2:grep=false"
) | Where-Object { $_ -ne "" }

if ($useWinlibDeps) {
    Write-Host "Using PHP SDK dependencies from $depsRoot"
    $mesonOptions += @(
        "--wrap-mode", "default",
        "--force-fallback-for", "libpcre2-8",
        "-Dwinlib_deps_root=`"$depsRoot`""
    )
} else {
    Write-Host "PHP SDK dependencies were not found at $depsRoot; using Meson fallback dependencies"
    $mesonOptions += @(
        "--wrap-mode", "forcefallback",
        "-Dlibffi:tests=false",
        "-Dzlib:tests=disabled",
        "-Dlibffi:default_library=static",
        "-Dzlib:default_library=static",
        "-Dproxy-libintl:default_library=static"
    )
}

$mesonSetupCommand = "`"$python`" -m mesonbuild.mesonmain " + ($mesonOptions -join " ")
$mesonInstallCommand = "`"$python`" -m mesonbuild.mesonmain install -C `"$buildDir`" --skip-subprojects"
$depsEnvCommands = ""
if ($useWinlibDeps) {
    $depsInclude = Join-Path $depsRoot "include"
    $depsLib = Join-Path $depsRoot "lib"
    $depsBin = Join-Path $depsRoot "bin"
    $depsEnvCommands = @"
set "INCLUDE=$depsInclude;!INCLUDE!"
set "LIB=$depsLib;!LIB!"
set "LIBPATH=$depsLib;!LIBPATH!"
set "PATH=$depsBin;!PATH!"
"@
}

$cmd = @"
@echo off
setlocal enabledelayedexpansion
call $vcVarsArgs
if errorlevel 1 exit /b !errorlevel!
"$python" -m pip install --user --disable-pip-version-check "meson==1.4.2" "ninja==1.11.1.1"
if errorlevel 1 exit /b !errorlevel!
set "PATH=$pythonDir;$pythonUserScripts;!PATH!"
$depsEnvCommands
if exist "$prefix" rmdir /s /q "$prefix"
$mesonSetupCommand
if errorlevel 1 exit /b !errorlevel!
$mesonInstallCommand
if errorlevel 1 exit /b !errorlevel!
endlocal
"@

Set-Content -Path $cmdFile -Value $cmd -Encoding ASCII
& cmd.exe /D /S /C "`"$cmdFile`""
if ($LASTEXITCODE -ne 0) {
    throw "Meson build failed with exit code $LASTEXITCODE"
}

if ($useLegacyDllNames) {
    $libDir = Join-Path $prefix "lib"
    $binDir = Join-Path $prefix "bin"
    $legacyImportLibraries = @(
        @("gio-2.lib", "gio-2.0.lib"),
        @("glib-2.lib", "glib-2.0.lib"),
        @("gmodule-2.lib", "gmodule-2.0.lib"),
        @("gobject-2.lib", "gobject-2.0.lib"),
        @("gthread-2.lib", "gthread-2.0.lib")
    )

    foreach ($pair in $legacyImportLibraries) {
        $source = Join-Path $libDir $pair[0]
        $target = Join-Path $libDir $pair[1]
        if (-not (Test-Path $source)) {
            throw "Expected import library $source was not found"
        }
        Copy-Item -Force $source $target
        Remove-Item -Force $source
        if (-not (Test-Path $target)) {
            throw "Expected import library $target was not found"
        }
        if (Test-Path $source) {
            throw "Unexpected import library $source was installed"
        }
    }

    $pkgConfigDir = Join-Path $libDir "pkgconfig"
    if (Test-Path $pkgConfigDir) {
        Remove-Item -Recurse -Force $pkgConfigDir
    }

    $expectedDlls = @(
        "gio-2.dll",
        "glib-2.dll",
        "gmodule-2.dll",
        "gobject-2.dll",
        "gthread-2.dll"
    )
    foreach ($dll in $expectedDlls) {
        $path = Join-Path $binDir $dll
        if (-not (Test-Path $path)) {
            throw "Expected legacy DLL $path was not found"
        }
    }

    $unexpectedDlls = @(
        "gio-2.0-0.dll",
        "glib-2.0-0.dll",
        "gmodule-2.0-0.dll",
        "gobject-2.0-0.dll",
        "gthread-2.0-0.dll"
    )
    foreach ($dll in $unexpectedDlls) {
        $path = Join-Path $binDir $dll
        if (Test-Path $path) {
            throw "Unexpected upstream DLL name $path was installed"
        }
    }

    Get-ChildItem (Join-Path $binDir "*") -File -Include *.dll, *.exe | ForEach-Object {
        $pdb = [System.IO.Path]::ChangeExtension($_.FullName, ".pdb")
        if (-not (Test-Path $pdb)) {
            throw "Expected PDB $pdb was not found"
        }
    }
}
