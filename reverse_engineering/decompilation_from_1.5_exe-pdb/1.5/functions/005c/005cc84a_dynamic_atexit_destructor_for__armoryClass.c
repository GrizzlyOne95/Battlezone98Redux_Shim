/*
 * Entry: 005cc84a
 * Name: `dynamic_atexit_destructor_for_'armoryClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'armoryClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__armoryClass__(void)

{
  armoryClass._padding_ = (int)&ArmoryClass::_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)&armoryClass);
  return;
}
