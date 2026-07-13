/*
 * Entry: 0045c9d5
 * Name: ScavengerProcess::Load
 * Namespace: ScavengerProcess
 * Signature: bool Load(ScavengerProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavengerProcess::Load(ScavengerProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->oldhealth,4);
  if (((((bVar1) && (bVar1 = ::in(param_1,(int *)&this->curState,4), bVar1)) &&
       (bVar1 = ::in(param_1,(int *)&this->nextState,4), bVar1)) &&
      ((((bVar1 = ::in(param_1,&this->whoHandle,4), bVar1 &&
         (bVar1 = in_ptr(param_1,&this->craft,4,"craft",this), bVar1)) &&
        ((bVar1 = ::in(param_1,&this->where,0xc), bVar1 &&
         ((bVar1 = ::in(param_1,&this->lastScrap,0xc), bVar1 &&
          (bVar1 = ::in(param_1,&this->wait_time,4), bVar1)))))) &&
       (bVar1 = ::in(param_1,&this->recycle,1), bVar1)))) &&
     (((bVar1 = ::in(param_1,&this->team,4), bVar1 &&
       (bVar1 = in_ptr(param_1,&this->task,4,"task",this), bVar1)) &&
      (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
