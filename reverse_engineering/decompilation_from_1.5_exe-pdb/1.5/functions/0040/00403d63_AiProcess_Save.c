/*
 * Entry: 00403d63
 * Name: AiProcess::Save
 * Namespace: AiProcess
 * Signature: bool Save(AiProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiProcess::Save(AiProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = out_ptr(param_1,&this->fMission,4,"fMission");
  if (((bVar1) && (bVar1 = out_ptr(param_1,&this->fOwner,4,"fOwner"), bVar1)) &&
     (bVar1 = ::out(param_1,&this->exited,4,"exited"), bVar1)) {
    return true;
  }
  return false;
}
