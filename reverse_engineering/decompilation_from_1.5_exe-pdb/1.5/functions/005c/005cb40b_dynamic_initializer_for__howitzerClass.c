/*
 * Entry: 005cb40b
 * Name: `dynamic_initializer_for_'howitzerClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'howitzerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__howitzerClass__(void)

{
  HowitzerClass::HowitzerClass((HowitzerClass *)&howitzerClass);
  atexit(_dynamic_atexit_destructor_for__howitzerClass__);
  return;
}
