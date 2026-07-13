/*
 * Entry: 00453fb0
 * Name: PathPlan::`scalar_deleting_destructor'
 * Namespace: PathPlan
 * Signature: void * `scalar_deleting_destructor'(PathPlan * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PathPlan::_scalar_deleting_destructor_(PathPlan *this,uint param_1)

{
  PathPoint *pPVar1;
  
  this->_padding_ = (int)&_vftable_;
  pPVar1 = (this->points)._Myfirst;
  if (pPVar1 != (PathPoint *)0x0) {
    ::operator_delete(pPVar1);
  }
  (this->points)._Myfirst = (PathPoint *)0x0;
  (this->points)._Mylast = (PathPoint *)0x0;
  (this->points)._Myend = (PathPoint *)0x0;
  ::operator_delete((void *)(this->points)._padding_);
  if ((param_1 & 1) != 0) {
    MemoryPool::Free(&planPool,this);
  }
  return this;
}
