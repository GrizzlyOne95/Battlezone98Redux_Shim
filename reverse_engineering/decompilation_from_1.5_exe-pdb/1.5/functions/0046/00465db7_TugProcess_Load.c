/*
 * Entry: 00465db7
 * Name: TugProcess::Load
 * Namespace: TugProcess
 * Signature: bool Load(TugProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TugProcess::Load(TugProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,(int *)&this->curState,4);
  if ((((((bVar1) && (bVar1 = ::in(param_1,(int *)&this->nextState,4), bVar1)) &&
        (bVar1 = in_ptr(param_1,&this->craft,4,"craft",this), bVar1)) &&
       ((bVar1 = ::in(param_1,&this->where,0xc), bVar1 &&
        (bVar1 = ::in(param_1,&this->whoHandle,4), bVar1)))) &&
      ((bVar1 = in_ptr(param_1,&this->task,4,"task",this), bVar1 &&
       ((bVar1 = ::in(param_1,&this->dropoffPoint,4), bVar1 &&
        (bVar1 = ::in(param_1,&this->tugLocation,0xc), bVar1)))))) &&
     (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
