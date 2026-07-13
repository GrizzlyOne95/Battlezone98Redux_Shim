/*
 * Entry: 00413904
 * Name: GotoTask::Save
 * Namespace: GotoTask
 * Signature: bool Save(GotoTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GotoTask::Save(GotoTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = out_ptr(param_1,&this->path,4,"path");
  if ((((bVar1) && (bVar1 = ::out(param_1,&this->pathPoint,4,"pathPoint"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->release,1,"release"), bVar1)) &&
     (((bVar1 = ::out(param_1,&this->exact,1,"exact"), bVar1 &&
       (bVar1 = ::out(param_1,&this->destPoint,0xc,"destPoint"), bVar1)) &&
      (bVar1 = UnitTask::Save((UnitTask *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
