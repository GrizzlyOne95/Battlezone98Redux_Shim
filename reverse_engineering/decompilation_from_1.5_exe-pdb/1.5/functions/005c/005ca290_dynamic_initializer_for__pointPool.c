/*
 * Entry: 005ca290
 * Name: `dynamic_initializer_for_'pointPool''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'pointPool''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__pointPool__(void)

{
  MemoryPool::MemoryPool(&pointPool,0x10,0x400,0x80);
  atexit(_dynamic_atexit_destructor_for__pointPool__);
  return;
}
