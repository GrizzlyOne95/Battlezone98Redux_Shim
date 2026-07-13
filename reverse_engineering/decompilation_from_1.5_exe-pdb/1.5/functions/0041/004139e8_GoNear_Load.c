/*
 * Entry: 004139e8
 * Name: GoNear::Load
 * Namespace: GoNear
 * Signature: bool Load(GoNear * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoNear::Load(GoNear *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->nearSq,4);
  if ((((bVar1) && (bVar1 = ::in(param_1,&this->wasNear,1), bVar1)) &&
      (bVar1 = ::in(param_1,&this->nearTime,4), bVar1)) &&
     (bVar1 = GotoTask::Load((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
