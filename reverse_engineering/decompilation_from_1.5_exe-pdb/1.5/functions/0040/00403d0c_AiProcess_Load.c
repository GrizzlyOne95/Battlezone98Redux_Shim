/*
 * Entry: 00403d0c
 * Name: AiProcess::Load
 * Namespace: AiProcess
 * Signature: bool Load(AiProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiProcess::Load(AiProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,&this->fMission,4,"AiProcess",this);
  if (((bVar1) && (bVar1 = in_ptr(param_1,&this->fOwner,4,"AiProcess",this), bVar1)) &&
     (bVar1 = ::in(param_1,&this->exited,4), bVar1)) {
    return true;
  }
  return false;
}
