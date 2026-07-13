/*
 * Entry: 005cbf30
 * Name: `dynamic_initializer_for_'grenadeClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'grenadeClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__grenadeClass__(void)

{
  GrenadeClass::GrenadeClass(&grenadeClass);
  atexit(_dynamic_atexit_destructor_for__grenadeClass__);
  return;
}
