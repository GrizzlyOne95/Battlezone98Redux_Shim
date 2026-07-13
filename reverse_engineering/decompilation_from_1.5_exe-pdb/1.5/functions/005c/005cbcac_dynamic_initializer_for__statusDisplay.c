/*
 * Entry: 005cbcac
 * Name: `dynamic_initializer_for_'statusDisplay''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'statusDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__statusDisplay__(void)

{
  StatusDisplay::StatusDisplay(&statusDisplay);
  atexit(_dynamic_atexit_destructor_for__statusDisplay__);
  return;
}
