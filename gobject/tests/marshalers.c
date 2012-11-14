
#include	<glib-object.h>


#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_schar (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#define g_marshal_value_peek_variant(v)  g_value_get_variant (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_variant(v)  (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* VOID:INT,BOOLEAN,CHAR,UCHAR,UINT,LONG,ULONG,ENUM,FLAGS,FLOAT,DOUBLE,STRING,PARAM,BOXED,POINTER,OBJECT,VARIANT,INT64,UINT64 (./marshalers.list:1) */
void
test_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64 (GClosure     *closure,
                                                                                                                                  GValue       *return_value G_GNUC_UNUSED,
                                                                                                                                  guint         n_param_values,
                                                                                                                                  const GValue *param_values,
                                                                                                                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                                                                                                                  gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64) (gpointer     data1,
                                                                                                                                                            gint         arg_1,
                                                                                                                                                            gboolean     arg_2,
                                                                                                                                                            gchar        arg_3,
                                                                                                                                                            guchar       arg_4,
                                                                                                                                                            guint        arg_5,
                                                                                                                                                            glong        arg_6,
                                                                                                                                                            gulong       arg_7,
                                                                                                                                                            gint         arg_8,
                                                                                                                                                            guint        arg_9,
                                                                                                                                                            gfloat       arg_10,
                                                                                                                                                            gdouble      arg_11,
                                                                                                                                                            gpointer     arg_12,
                                                                                                                                                            gpointer     arg_13,
                                                                                                                                                            gpointer     arg_14,
                                                                                                                                                            gpointer     arg_15,
                                                                                                                                                            gpointer     arg_16,
                                                                                                                                                            gpointer     arg_17,
                                                                                                                                                            gint64       arg_18,
                                                                                                                                                            guint64      arg_19,
                                                                                                                                                            gpointer     data2);
  register GMarshalFunc_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64 callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 20);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_int (param_values + 1),
            g_marshal_value_peek_boolean (param_values + 2),
            g_marshal_value_peek_char (param_values + 3),
            g_marshal_value_peek_uchar (param_values + 4),
            g_marshal_value_peek_uint (param_values + 5),
            g_marshal_value_peek_long (param_values + 6),
            g_marshal_value_peek_ulong (param_values + 7),
            g_marshal_value_peek_enum (param_values + 8),
            g_marshal_value_peek_flags (param_values + 9),
            g_marshal_value_peek_float (param_values + 10),
            g_marshal_value_peek_double (param_values + 11),
            g_marshal_value_peek_string (param_values + 12),
            g_marshal_value_peek_param (param_values + 13),
            g_marshal_value_peek_boxed (param_values + 14),
            g_marshal_value_peek_pointer (param_values + 15),
            g_marshal_value_peek_object (param_values + 16),
            g_marshal_value_peek_variant (param_values + 17),
            g_marshal_value_peek_int64 (param_values + 18),
            g_marshal_value_peek_uint64 (param_values + 19),
            data2);
}
void
test_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64v (GClosure     *closure,
                                                                                                                                   GValue       *return_value,
                                                                                                                                   gpointer      instance,
                                                                                                                                   va_list       args,
                                                                                                                                   gpointer      marshal_data,
                                                                                                                                   int           n_params,
                                                                                                                                   GType        *param_types)
{
  typedef void (*GMarshalFunc_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64) (gpointer     instance,
                                                                                                                                                            gint         arg_0,
                                                                                                                                                            gboolean     arg_1,
                                                                                                                                                            gchar        arg_2,
                                                                                                                                                            guchar       arg_3,
                                                                                                                                                            guint        arg_4,
                                                                                                                                                            glong        arg_5,
                                                                                                                                                            gulong       arg_6,
                                                                                                                                                            gint         arg_7,
                                                                                                                                                            guint        arg_8,
                                                                                                                                                            gfloat       arg_9,
                                                                                                                                                            gdouble      arg_10,
                                                                                                                                                            gpointer     arg_11,
                                                                                                                                                            gpointer     arg_12,
                                                                                                                                                            gpointer     arg_13,
                                                                                                                                                            gpointer     arg_14,
                                                                                                                                                            gpointer     arg_15,
                                                                                                                                                            gpointer     arg_16,
                                                                                                                                                            gint64       arg_17,
                                                                                                                                                            guint64      arg_18,
                                                                                                                                                            gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64 callback;
  gint arg0;
  gboolean arg1;
  gchar arg2;
  guchar arg3;
  guint arg4;
  glong arg5;
  gulong arg6;
  gint arg7;
  guint arg8;
  gfloat arg9;
  gdouble arg10;
  gpointer arg11;
  gpointer arg12;
  gpointer arg13;
  gpointer arg14;
  gpointer arg15;
  gpointer arg16;
  gint64 arg17;
  guint64 arg18;
  va_list args_copy;

  G_VA_COPY (args_copy, args);
  arg0 = (gint) va_arg (args_copy, gint);
  arg1 = (gboolean) va_arg (args_copy, gboolean);
  arg2 = (gchar) va_arg (args_copy, gint);
  arg3 = (guchar) va_arg (args_copy, guint);
  arg4 = (guint) va_arg (args_copy, guint);
  arg5 = (glong) va_arg (args_copy, glong);
  arg6 = (gulong) va_arg (args_copy, gulong);
  arg7 = (gint) va_arg (args_copy, gint);
  arg8 = (guint) va_arg (args_copy, guint);
  arg9 = (gfloat) va_arg (args_copy, gdouble);
  arg10 = (gdouble) va_arg (args_copy, gdouble);
  arg11 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[11] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg11 != NULL)
    arg11 = g_strdup (arg11);
  arg12 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[12] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg12 != NULL)
    arg12 = g_param_spec_ref (arg12);
  arg13 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[13] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg13 != NULL)
    arg13 = g_boxed_copy (param_types[13] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg13);
  arg14 = (gpointer) va_arg (args_copy, gpointer);
  arg15 = (gpointer) va_arg (args_copy, gpointer);
  if (arg15 != NULL)
    arg15 = g_object_ref (arg15);
  arg16 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[16] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg16 != NULL)
    arg16 = g_variant_ref_sink (arg16);
  arg17 = (gint64) va_arg (args_copy, gint64);
  arg18 = (guint64) va_arg (args_copy, guint64);
  va_end (args_copy);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = instance;
    }
  else
    {
      data1 = instance;
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__INT_BOOLEAN_CHAR_UCHAR_UINT_LONG_ULONG_ENUM_FLAGS_FLOAT_DOUBLE_STRING_PARAM_BOXED_POINTER_OBJECT_VARIANT_INT64_UINT64) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            arg0,
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6,
            arg7,
            arg8,
            arg9,
            arg10,
            arg11,
            arg12,
            arg13,
            arg14,
            arg15,
            arg16,
            arg17,
            arg18,
            data2);
  if ((param_types[11] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg11 != NULL)
    g_free (arg11);
  if ((param_types[12] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg12 != NULL)
    g_param_spec_unref (arg12);
  if ((param_types[13] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg13 != NULL)
    g_boxed_free (param_types[13] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg13);
  if (arg15 != NULL)
    g_object_unref (arg15);
  if ((param_types[16] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg16 != NULL)
    g_variant_unref (arg16);
}


/* INT:VOID (./marshalers.list:2) */
void
test_INT__VOID (GClosure     *closure,
                GValue       *return_value G_GNUC_UNUSED,
                guint         n_param_values,
                const GValue *param_values,
                gpointer      invocation_hint G_GNUC_UNUSED,
                gpointer      marshal_data)
{
  typedef gint (*GMarshalFunc_INT__VOID) (gpointer     data1,
                                          gpointer     data2);
  register GMarshalFunc_INT__VOID callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gint v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 1);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_INT__VOID) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       data2);

  g_value_set_int (return_value, v_return);
}
void
test_INT__VOIDv (GClosure     *closure,
                 GValue       *return_value,
                 gpointer      instance,
                 va_list       args,
                 gpointer      marshal_data,
                 int           n_params,
                 GType        *param_types)
{
  typedef gint (*GMarshalFunc_INT__VOID) (gpointer     instance,
                                          gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_INT__VOID callback;
  gint v_return;

  g_return_if_fail (return_value != NULL);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = instance;
    }
  else
    {
      data1 = instance;
      data2 = closure->data;
    }
  callback = (GMarshalFunc_INT__VOID) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       data2);

  g_value_set_int (return_value, v_return);
}


/* UINT:VOID (./marshalers.list:3) */
void
test_UINT__VOID (GClosure     *closure,
                 GValue       *return_value G_GNUC_UNUSED,
                 guint         n_param_values,
                 const GValue *param_values,
                 gpointer      invocation_hint G_GNUC_UNUSED,
                 gpointer      marshal_data)
{
  typedef guint (*GMarshalFunc_UINT__VOID) (gpointer     data1,
                                            gpointer     data2);
  register GMarshalFunc_UINT__VOID callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  guint v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 1);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_UINT__VOID) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       data2);

  g_value_set_uint (return_value, v_return);
}
void
test_UINT__VOIDv (GClosure     *closure,
                  GValue       *return_value,
                  gpointer      instance,
                  va_list       args,
                  gpointer      marshal_data,
                  int           n_params,
                  GType        *param_types)
{
  typedef guint (*GMarshalFunc_UINT__VOID) (gpointer     instance,
                                            gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_UINT__VOID callback;
  guint v_return;

  g_return_if_fail (return_value != NULL);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = instance;
    }
  else
    {
      data1 = instance;
      data2 = closure->data;
    }
  callback = (GMarshalFunc_UINT__VOID) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       data2);

  g_value_set_uint (return_value, v_return);
}


