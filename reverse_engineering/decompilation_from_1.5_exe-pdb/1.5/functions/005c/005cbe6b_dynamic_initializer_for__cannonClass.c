/*
 * Entry: 005cbe6b
 * Name: `dynamic_initializer_for_'cannonClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'cannonClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__cannonClass__(void)

{
  CannonClass::CannonClass(&cannonClass);
  atexit(_dynamic_atexit_destructor_for__cannonClass__);
  return;
}
