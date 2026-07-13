/*
 * Entry: 005cbeee
 * Name: `dynamic_initializer_for_'explosionClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'explosionClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__explosionClass__(void)

{
  ExplosionClass::ExplosionClass(&explosionClass);
  atexit(_dynamic_atexit_destructor_for__explosionClass__);
  return;
}
