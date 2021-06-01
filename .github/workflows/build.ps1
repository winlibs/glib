param (
    [Parameter(Mandatory)] $vs,
    [Parameter(Mandatory)] $arch,
    [Parameter(Mandatory)] $libffi,
    [Parameter(Mandatory)] $libintl,
    [Parameter(Mandatory)] $zlib
)

$ErrorActionPreference = "Stop"

$deps = New-Item "winlib_deps" -ItemType "directory"

$temp = New-TemporaryFile | Rename-Item -NewName {$_.Name + ".zip"} -PassThru
Invoke-WebRequest "https://windows.php.net/downloads/php-sdk/deps/$vs/$arch/libffi-$libffi-$vs-$arch.zip" -OutFile $temp
Expand-Archive $temp -DestinationPath "winlib_deps"

$temp = New-TemporaryFile | Rename-Item -NewName {$_.Name + ".zip"} -PassThru
Invoke-WebRequest "https://windows.php.net/downloads/php-sdk/deps/$vs/$arch/libintl-$libintl-$vs-$arch.zip" -OutFile $temp
Expand-Archive $temp -DestinationPath "winlib_deps"

$temp = New-TemporaryFile | Rename-Item -NewName {$_.Name + ".zip"} -PassThru
Invoke-WebRequest "https://windows.php.net/downloads/php-sdk/deps/$vs/$arch/zlib-$zlib-$vs-$arch.zip" -OutFile $temp
Expand-Archive $temp -DestinationPath "winlib_deps"

$Env:INCLUDE="$deps\include;$Env:INCLUDE"
$Env:LIB="$deps\lib;$Env:LIB"
msbuild "/p:Configuration=Release_BundledPCRE" "/p:Platform=$arch" "/p:useenv=true" "win32\vs$($vs.substring(2))\glib.sln"

xcopy "/e" "..\vs$($vs.substring(2))\$arch" "winlib_build\*"
