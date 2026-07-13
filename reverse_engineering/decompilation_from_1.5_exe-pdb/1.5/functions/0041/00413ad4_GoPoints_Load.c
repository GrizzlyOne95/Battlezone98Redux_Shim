/*
 * Entry: 00413ad4
 * Name: GoPoints::Load
 * Namespace: GoPoints
 * Signature: bool Load(GoPoints * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoPoints::Load(GoPoints *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,&this->lastPlan,4,"lastPlan",this);
  if ((bVar1) && (bVar1 = GotoTask::Load((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
