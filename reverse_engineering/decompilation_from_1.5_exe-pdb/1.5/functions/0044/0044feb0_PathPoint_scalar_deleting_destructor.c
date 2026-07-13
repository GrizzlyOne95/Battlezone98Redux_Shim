/*
 * Entry: 0044feb0
 * Name: PathPoint::`scalar_deleting_destructor'
 * Namespace: PathPoint
 * Signature: void * `scalar_deleting_destructor'(PathPoint * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PathPoint::_scalar_deleting_destructor_(PathPoint *this,uint param_1)

{
  if ((param_1 & 1) != 0) {
    MemoryPool::Free(&pointPool,this);
  }
  return this;
}
