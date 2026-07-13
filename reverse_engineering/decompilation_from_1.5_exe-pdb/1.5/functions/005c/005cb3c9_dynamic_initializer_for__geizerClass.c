/*
 * Entry: 005cb3c9
 * Name: `dynamic_initializer_for_'geizerClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'geizerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__geizerClass__(void)

{
  GeizerClass::GeizerClass(&geizerClass);
  atexit(_dynamic_atexit_destructor_for__geizerClass__);
  return;
}
