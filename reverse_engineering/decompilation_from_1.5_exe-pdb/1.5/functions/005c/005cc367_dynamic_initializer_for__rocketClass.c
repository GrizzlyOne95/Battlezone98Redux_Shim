/*
 * Entry: 005cc367
 * Name: `dynamic_initializer_for_'rocketClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'rocketClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__rocketClass__(void)

{
  RocketClass::RocketClass(&rocketClass);
  atexit(_dynamic_atexit_destructor_for__rocketClass__);
  return;
}
