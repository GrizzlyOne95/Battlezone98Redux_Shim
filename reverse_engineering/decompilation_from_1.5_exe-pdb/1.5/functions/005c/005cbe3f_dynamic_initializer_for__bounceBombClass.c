/*
 * Entry: 005cbe3f
 * Name: `dynamic_initializer_for_'bounceBombClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'bounceBombClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__bounceBombClass__(void)

{
  BounceBombClass::BounceBombClass(&bounceBombClass);
  atexit(_dynamic_atexit_destructor_for__bounceBombClass__);
  return;
}
