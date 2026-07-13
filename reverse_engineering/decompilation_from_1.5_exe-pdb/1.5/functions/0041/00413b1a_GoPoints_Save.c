/*
 * Entry: 00413b1a
 * Name: GoPoints::Save
 * Namespace: GoPoints
 * Signature: bool Save(GoPoints * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoPoints::Save(GoPoints *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = out_ptr(param_1,&this->lastPlan,4,"lastPlan");
  if ((bVar1) && (bVar1 = GotoTask::Save((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
