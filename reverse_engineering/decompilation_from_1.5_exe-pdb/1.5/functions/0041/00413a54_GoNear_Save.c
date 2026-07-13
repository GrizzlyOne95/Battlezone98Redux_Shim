/*
 * Entry: 00413a54
 * Name: GoNear::Save
 * Namespace: GoNear
 * Signature: bool Save(GoNear * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoNear::Save(GoNear *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->nearSq,4,"nearSq");
  if ((((bVar1) && (bVar1 = ::out(param_1,&this->wasNear,1,"wasNear"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->nearTime,4,"nearTime"), bVar1)) &&
     (bVar1 = GotoTask::Save((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
