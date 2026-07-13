/*
 * Entry: 0044e510
 * Name: PathPoint::operator_new
 * Namespace: PathPoint
 * Signature: void * operator_new(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl PathPoint::operator_new(uint param_1)

{
  void *pvVar1;
  
  pvVar1 = MemoryPool::Alloc(&pointPool);
  return pvVar1;
}
