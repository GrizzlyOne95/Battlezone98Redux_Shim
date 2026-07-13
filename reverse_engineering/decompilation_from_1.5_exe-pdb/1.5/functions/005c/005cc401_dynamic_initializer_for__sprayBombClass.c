/*
 * Entry: 005cc401
 * Name: `dynamic_initializer_for_'sprayBombClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'sprayBombClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__sprayBombClass__(void)

{
  SprayBombClass::SprayBombClass(&sprayBombClass);
  atexit(_dynamic_atexit_destructor_for__sprayBombClass__);
  return;
}
