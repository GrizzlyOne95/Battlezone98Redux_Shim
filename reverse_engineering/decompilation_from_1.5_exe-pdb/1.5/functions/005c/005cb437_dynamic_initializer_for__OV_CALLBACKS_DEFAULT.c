/*
 * Entry: 005cb437
 * Name: `dynamic_initializer_for_'OV_CALLBACKS_DEFAULT''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'OV_CALLBACKS_DEFAULT''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__OV_CALLBACKS_DEFAULT__(void)

{
  OV_CALLBACKS_DEFAULT.read_func = fread_exref;
  OV_CALLBACKS_DEFAULT.close_func = fclose_exref;
  OV_CALLBACKS_DEFAULT.tell_func = ftell_exref;
  return;
}
