/*
 * Entry: 005cc6f0
 * Name: `dynamic_atexit_destructor_for_'planPool''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'planPool''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__planPool__(void)

{
  MemoryPool::~MemoryPool(&planPool);
  return;
}
