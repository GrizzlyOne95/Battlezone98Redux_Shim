/*
 * Entry: 005ca270
 * Name: `dynamic_initializer_for_'planPool''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'planPool''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__planPool__(void)

{
  MemoryPool::MemoryPool(&planPool,0x40,0x100,0x10);
  atexit(_dynamic_atexit_destructor_for__planPool__);
  return;
}
