/*
 * Entry: 005cbe29
 * Name: `dynamic_initializer_for_'boltClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'boltClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__boltClass__(void)

{
  BoltClass::BoltClass(&boltClass);
  atexit(_dynamic_atexit_destructor_for__boltClass__);
  return;
}
