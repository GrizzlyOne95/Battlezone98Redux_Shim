/*
 * Entry: 005cc4b1
 * Name: `dynamic_initializer_for_'tracerClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'tracerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__tracerClass__(void)

{
  TracerClass::TracerClass(&tracerClass);
  atexit(_dynamic_atexit_destructor_for__tracerClass__);
  return;
}
