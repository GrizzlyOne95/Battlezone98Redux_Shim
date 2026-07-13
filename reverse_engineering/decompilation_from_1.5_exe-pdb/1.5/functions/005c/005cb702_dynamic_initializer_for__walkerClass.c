/*
 * Entry: 005cb702
 * Name: `dynamic_initializer_for_'walkerClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'walkerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__walkerClass__(void)

{
  WalkerClass::WalkerClass(&walkerClass);
  atexit(_dynamic_atexit_destructor_for__walkerClass__);
  return;
}
