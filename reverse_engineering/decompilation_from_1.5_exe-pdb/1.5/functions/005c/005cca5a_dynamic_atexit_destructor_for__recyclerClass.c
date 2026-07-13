/*
 * Entry: 005cca5a
 * Name: `dynamic_atexit_destructor_for_'recyclerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'recyclerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__recyclerClass__(void)

{
  recyclerClass._0_4_ = &RecyclerClass::_vftable_;
  ProducerClass::~ProducerClass((ProducerClass *)&recyclerClass);
  return;
}
