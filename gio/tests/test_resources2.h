#ifndef __RESOURCE__g_test2_H__
#define __RESOURCE__g_test2_H__

#include <gio/gio.h>

extern GResource *_g_test2_get_resource (void);

extern void _g_test2_register_resource (void);
extern void _g_test2_unregister_resource (void);

#endif
