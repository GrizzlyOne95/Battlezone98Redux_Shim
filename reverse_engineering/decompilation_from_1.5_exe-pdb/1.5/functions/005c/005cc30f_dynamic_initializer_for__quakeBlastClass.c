/*
 * Entry: 005cc30f
 * Name: `dynamic_initializer_for_'quakeBlastClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'quakeBlastClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__quakeBlastClass__(void)

{
  QuakeBlastClass::QuakeBlastClass(&quakeBlastClass);
  atexit(_dynamic_atexit_destructor_for__quakeBlastClass__);
  return;
}
