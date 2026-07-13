/*
 * Entry: 005cb36b
 * Name: `dynamic_initializer_for_'factoryClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'factoryClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__factoryClass__(void)

{
  FactoryClass::FactoryClass((FactoryClass *)&factoryClass);
  atexit(_dynamic_atexit_destructor_for__factoryClass__);
  return;
}
