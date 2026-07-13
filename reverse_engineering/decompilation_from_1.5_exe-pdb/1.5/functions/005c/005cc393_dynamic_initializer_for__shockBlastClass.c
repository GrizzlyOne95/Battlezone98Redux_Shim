/*
 * Entry: 005cc393
 * Name: `dynamic_initializer_for_'shockBlastClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'shockBlastClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__shockBlastClass__(void)

{
  ShockBlastClass::ShockBlastClass(&shockBlastClass);
  atexit(_dynamic_atexit_destructor_for__shockBlastClass__);
  return;
}
