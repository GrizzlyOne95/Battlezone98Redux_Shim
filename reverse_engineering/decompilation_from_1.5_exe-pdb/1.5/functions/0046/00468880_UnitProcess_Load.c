/*
 * Entry: 00468880
 * Name: UnitProcess::Load
 * Namespace: UnitProcess
 * Signature: bool Load(UnitProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitProcess::Load(UnitProcess *this,_iobuf *param_1)

{
  bool bVar1;
  GameObjectClass *pGVar2;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  bVar1 = ::in(param_1,&this->independence,4);
  if ((((((bVar1) && (bVar1 = ::in(param_1,(int *)&this->curState,4), bVar1)) &&
        (bVar1 = ::in(param_1,(int *)&this->nextState,4), bVar1)) &&
       ((bVar1 = ::in(param_1,(int *)&this->saveState,4), bVar1 &&
        (bVar1 = ::in(param_1,(ulong *)&this->saveWho,4), bVar1)))) &&
      (((bVar1 = ::in(param_1,&this->nextEnemyCheck,4), bVar1 &&
        ((bVar1 = in_ptr(param_1,&this->me,4,"me",this), bVar1 &&
         (bVar1 = in_ptr(param_1,&this->task,4,"task",this), bVar1)))) &&
       (bVar1 = ::in(param_1,(ulong *)&this->whoHandle,4), bVar1)))) &&
     ((bVar1 = in_ptr(param_1,&this->where,4,"where",this), bVar1 &&
      (bVar1 = ::in(param_1,&this->release,1), bVar1)))) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (version < 0x40c) {
LAB_004689b0:
    if (bVar1) goto LAB_004689b8;
  }
  else {
    if ((!bVar1) || (bVar1 = ::in(param_1,&this->exact,1), !bVar1)) {
      bVar1 = false;
      goto LAB_004689b0;
    }
LAB_004689b8:
    bVar1 = ::in(param_1,(long64 *)&local_c,8);
    if ((((bVar1) && (bVar1 = ::in(param_1,&this->isInTransition,1), bVar1)) &&
        (bVar1 = ::in(param_1,&this->wasInTransition,1), bVar1)) &&
       (((bVar1 = ::in(param_1,&this->waitStart,4), bVar1 &&
         (bVar1 = ::in(param_1,&this->waitDeploy,1), bVar1)) &&
        ((bVar1 = ::in(param_1,&this->waitDeployTime,4), bVar1 &&
         (bVar1 = ::in(param_1,&this->timeOut,4), bVar1)))))) {
      bVar1 = true;
      goto LAB_00468a40;
    }
  }
  bVar1 = false;
LAB_00468a40:
  this->exact = false;
  if (local_c == 0 && local_8 == 0) {
    this->whatClass = (GameObjectClass *)0x0;
  }
  else {
    pGVar2 = GameObjectClass::Find(CONCAT44(local_8,local_c));
    this->whatClass = pGVar2;
  }
  if ((bVar1) && (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
