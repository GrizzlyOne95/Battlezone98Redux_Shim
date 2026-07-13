/*
 * Entry: 0045cae2
 * Name: ScavengerProcess::Save
 * Namespace: ScavengerProcess
 * Signature: bool Save(ScavengerProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavengerProcess::Save(ScavengerProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->oldhealth,4,"oldhealth");
  if (((((bVar1) && (bVar1 = ::out(param_1,(int *)&this->curState,4,"curState"), bVar1)) &&
       (bVar1 = ::out(param_1,(int *)&this->nextState,4,"nextState"), bVar1)) &&
      ((((bVar1 = ::out(param_1,&this->whoHandle,4,"whoHandle"), bVar1 &&
         (bVar1 = out_ptr(param_1,&this->craft,4,"craft"), bVar1)) &&
        ((bVar1 = ::out(param_1,&this->where,0xc,"where"), bVar1 &&
         ((bVar1 = ::out(param_1,&this->lastScrap,0xc,"lastScrap"), bVar1 &&
          (bVar1 = ::out(param_1,&this->wait_time,4,"wait_time"), bVar1)))))) &&
       (bVar1 = ::out(param_1,&this->recycle,1,"recycle"), bVar1)))) &&
     (((bVar1 = ::out(param_1,&this->team,4,"team"), bVar1 &&
       (bVar1 = out_ptr(param_1,&this->task,4,"task"), bVar1)) &&
      (bVar1 = AiProcess::Save((AiProcess *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
