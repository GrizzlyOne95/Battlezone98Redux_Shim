/*
 * Entry: 005cbdfd
 * Name: `dynamic_initializer_for_'beamClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'beamClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__beamClass__(void)

{
  BeamClass::BeamClass(&beamClass);
  atexit(_dynamic_atexit_destructor_for__beamClass__);
  return;
}
