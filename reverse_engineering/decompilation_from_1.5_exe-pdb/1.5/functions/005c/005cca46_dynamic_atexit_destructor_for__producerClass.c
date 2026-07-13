/*
 * Entry: 005cca46
 * Name: `dynamic_atexit_destructor_for_'producerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'producerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__producerClass__(void)

{
  producerClass._padding_ = (int)&ProducerClass::_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)&producerClass);
  return;
}
