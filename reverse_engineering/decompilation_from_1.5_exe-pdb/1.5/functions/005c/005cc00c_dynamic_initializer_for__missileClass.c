/*
 * Entry: 005cc00c
 * Name: `dynamic_initializer_for_'missileClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'missileClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__missileClass__(void)

{
  MissileClass::MissileClass(&missileClass);
  atexit(_dynamic_atexit_destructor_for__missileClass__);
  return;
}
