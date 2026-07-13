/*
 * Entry: 0044e4f0
 * Name: PathPlan::operator_new
 * Namespace: PathPlan
 * Signature: void * operator_new(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl PathPlan::operator_new(uint param_1)

{
  void *pvVar1;
  
  pvVar1 = MemoryPool::Alloc(&planPool);
  return pvVar1;
}
