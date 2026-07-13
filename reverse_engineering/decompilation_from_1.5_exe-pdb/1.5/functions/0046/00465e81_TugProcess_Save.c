/*
 * Entry: 00465e81
 * Name: TugProcess::Save
 * Namespace: TugProcess
 * Signature: bool Save(TugProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TugProcess::Save(TugProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,(int *)&this->curState,4,"curState");
  if ((((((bVar1) && (bVar1 = ::out(param_1,(int *)&this->nextState,4,"nextState"), bVar1)) &&
        (bVar1 = out_ptr(param_1,&this->craft,4,"craft"), bVar1)) &&
       ((bVar1 = ::out(param_1,&this->where,0xc,"where"), bVar1 &&
        (bVar1 = ::out(param_1,&this->whoHandle,4,"whoHandle"), bVar1)))) &&
      ((bVar1 = out_ptr(param_1,&this->task,4,"task"), bVar1 &&
       ((bVar1 = ::out(param_1,&this->dropoffPoint,4,"dropoffPoint"), bVar1 &&
        (bVar1 = ::out(param_1,&this->tugLocation,0xc,"tugLocation"), bVar1)))))) &&
     (bVar1 = AiProcess::Save((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
