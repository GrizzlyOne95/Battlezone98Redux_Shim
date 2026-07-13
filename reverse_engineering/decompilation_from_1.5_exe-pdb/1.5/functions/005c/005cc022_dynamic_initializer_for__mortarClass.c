/*
 * Entry: 005cc022
 * Name: `dynamic_initializer_for_'mortarClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'mortarClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__mortarClass__(void)

{
  MortarClass::MortarClass(&mortarClass);
  atexit(_dynamic_atexit_destructor_for__mortarClass__);
  return;
}
