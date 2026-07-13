/*
 * Entry: 005cbff6
 * Name: `dynamic_initializer_for_'mineClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'mineClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__mineClass__(void)

{
  MineClass::MineClass(&mineClass);
  atexit(_dynamic_atexit_destructor_for__mineClass__);
  return;
}
