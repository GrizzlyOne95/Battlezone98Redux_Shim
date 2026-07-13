/*
 * Entry: 005cc700
 * Name: `dynamic_atexit_destructor_for_'pointPool''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'pointPool''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__pointPool__(void)

{
  MemoryPool::~MemoryPool(&pointPool);
  return;
}
