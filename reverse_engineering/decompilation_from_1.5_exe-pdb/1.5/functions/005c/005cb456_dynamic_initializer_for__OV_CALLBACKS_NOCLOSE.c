/*
 * Entry: 005cb456
 * Name: `dynamic_initializer_for_'OV_CALLBACKS_NOCLOSE''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'OV_CALLBACKS_NOCLOSE''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__OV_CALLBACKS_NOCLOSE__(void)

{
  OV_CALLBACKS_NOCLOSE.read_func = fread_exref;
  OV_CALLBACKS_NOCLOSE.tell_func = ftell_exref;
  return;
}
