/*
 * Entry: 00452c40
 * Name: PathPlan::~PathPlan
 * Namespace: PathPlan
 * Signature: void ~PathPlan(PathPlan * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathPlan::~PathPlan(PathPlan *this)

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
  return;
}
