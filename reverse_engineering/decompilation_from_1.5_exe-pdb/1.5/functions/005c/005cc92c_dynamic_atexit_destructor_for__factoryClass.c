/*
 * Entry: 005cc92c
 * Name: `dynamic_atexit_destructor_for_'factoryClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'factoryClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__factoryClass__(void)

{
  factoryClass._0_4_ = &FactoryClass::_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)&factoryClass);
  return;
}
