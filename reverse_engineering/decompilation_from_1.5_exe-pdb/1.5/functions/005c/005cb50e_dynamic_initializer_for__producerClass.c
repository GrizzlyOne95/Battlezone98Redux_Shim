/*
 * Entry: 005cb50e
 * Name: `dynamic_initializer_for_'producerClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'producerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__producerClass__(void)

{
  ProducerClass::ProducerClass((ProducerClass *)&producerClass);
  atexit(_dynamic_atexit_destructor_for__producerClass__);
  return;
}
