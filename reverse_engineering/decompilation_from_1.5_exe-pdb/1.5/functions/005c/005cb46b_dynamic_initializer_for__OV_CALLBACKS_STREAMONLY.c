/*
 * Entry: 005cb46b
 * Name: `dynamic_initializer_for_'OV_CALLBACKS_STREAMONLY''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'OV_CALLBACKS_STREAMONLY''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__OV_CALLBACKS_STREAMONLY__(void)

{
  OV_CALLBACKS_STREAMONLY.read_func = fread_exref;
  OV_CALLBACKS_STREAMONLY.close_func = fclose_exref;
  return;
}
