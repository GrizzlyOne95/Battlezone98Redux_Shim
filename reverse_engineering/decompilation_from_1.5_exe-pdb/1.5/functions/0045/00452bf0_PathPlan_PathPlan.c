/*
 * Entry: 00452bf0
 * Name: PathPlan::PathPlan
 * Namespace: PathPlan
 * Signature: PathPlan * PathPlan(PathPlan * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPlan * __thiscall PathPlan::PathPlan(PathPlan *this)

{
  int *piVar1;
  
  this->_padding_ = (int)&_vftable_;
  piVar1 = ::operator_new(4);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    *piVar1 = (int)&this->points;
  }
  (this->points)._padding_ = (int)piVar1;
  (this->points)._Myfirst = (PathPoint *)0x0;
  (this->points)._Mylast = (PathPoint *)0x0;
  (this->points)._Myend = (PathPoint *)0x0;
  (this->lastPos).x = 0.0;
  (this->lastPos).z = 0.0;
  this->curPoint = 0;
  this->lastCurPoint = -1;
  this->timeOut = 0;
  this->lastChange = 0;
  return this;
}
