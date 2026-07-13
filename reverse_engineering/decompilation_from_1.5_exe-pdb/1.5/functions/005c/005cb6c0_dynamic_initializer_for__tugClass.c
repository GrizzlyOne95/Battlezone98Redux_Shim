/*
 * Entry: 005cb6c0
 * Name: `dynamic_initializer_for_'tugClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'tugClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__tugClass__(void)

{
  TugClass::TugClass((TugClass *)&tugClass);
  atexit(_dynamic_atexit_destructor_for__tugClass__);
  return;
}
