/*
 * Entry: 005cb4b6
 * Name: `dynamic_initializer_for_'personClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'personClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__personClass__(void)

{
  PersonClass::PersonClass(&personClass);
  atexit(_dynamic_atexit_destructor_for__personClass__);
  return;
}
