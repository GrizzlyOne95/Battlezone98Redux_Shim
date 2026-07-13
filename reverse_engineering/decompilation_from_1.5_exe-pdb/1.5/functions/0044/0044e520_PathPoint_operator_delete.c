/*
 * Entry: 0044e520
 * Name: PathPoint::operator_delete
 * Namespace: PathPoint
 * Signature: void operator_delete(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PathPoint::operator_delete(void *param_1)

{
  MemoryPool::Free(&pointPool,param_1);
  return;
}
