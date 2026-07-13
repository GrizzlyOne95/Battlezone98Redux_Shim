/*
 * Entry: 0041384a
 * Name: GotoTask::Load
 * Namespace: GotoTask
 * Signature: bool Load(GotoTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GotoTask::Load(GotoTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,&this->path,4,"path",this);
  if (((bVar1) && (bVar1 = ::in(param_1,&this->pathPoint,4), bVar1)) &&
     (bVar1 = ::in(param_1,&this->release,1), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (0x40b < version) {
    if ((bVar1) && (bVar1 = ::in(param_1,&this->exact,1), bVar1)) goto LAB_004138cc;
    bVar1 = false;
  }
  if (!bVar1) {
    return false;
  }
LAB_004138cc:
  bVar1 = ::in(param_1,&this->destPoint,0xc);
  if ((bVar1) && (bVar1 = UnitTask::Load((UnitTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
