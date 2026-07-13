/*
 * Entry: 0044e500
 * Name: PathPlan::operator_delete
 * Namespace: PathPlan
 * Signature: void operator_delete(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PathPlan::operator_delete(void *param_1)

{
  MemoryPool::Free(&planPool,param_1);
  return;
}
