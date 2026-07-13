/*
 * Entry: 005cbe55
 * Name: `dynamic_initializer_for_'bulletClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'bulletClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__bulletClass__(void)

{
  BulletClass::BulletClass(&bulletClass);
  atexit(_dynamic_atexit_destructor_for__bulletClass__);
  return;
}
