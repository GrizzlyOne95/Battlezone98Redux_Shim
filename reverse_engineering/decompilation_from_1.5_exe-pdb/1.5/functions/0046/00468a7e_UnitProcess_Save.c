/*
 * Entry: 00468a7e
 * Name: UnitProcess::Save
 * Namespace: UnitProcess
 * Signature: bool Save(UnitProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitProcess::Save(UnitProcess *this,_iobuf *param_1)

{
  GameObjectClass *pGVar1;
  bool bVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  local_8 = 0;
  pGVar1 = this->whatClass;
  if (pGVar1 != (GameObjectClass *)0x0) {
    local_c = (undefined4)pGVar1->cfg;
    local_8 = *(undefined4 *)((int)&pGVar1->cfg + 4);
  }
  bVar2 = ::out(param_1,&this->independence,4,"independence");
  if (((((((bVar2) && (bVar2 = ::out(param_1,(int *)&this->curState,4,"curState"), bVar2)) &&
         (bVar2 = ::out(param_1,(int *)&this->nextState,4,"nextState"), bVar2)) &&
        ((bVar2 = ::out(param_1,(int *)&this->saveState,4,"saveState"), bVar2 &&
         (bVar2 = ::out(param_1,(ulong *)&this->saveWho,4,"saveWho"), bVar2)))) &&
       (((bVar2 = ::out(param_1,&this->nextEnemyCheck,4,"nextEnemyCheck"), bVar2 &&
         ((bVar2 = out_ptr(param_1,&this->me,4,"me"), bVar2 &&
          (bVar2 = out_ptr(param_1,&this->task,4,"task"), bVar2)))) &&
        (bVar2 = ::out(param_1,(ulong *)&this->whoHandle,4,"whoHandle"), bVar2)))) &&
      ((((bVar2 = out_ptr(param_1,&this->where,4,"where"), bVar2 &&
         (bVar2 = ::out(param_1,&this->release,1,"release"), bVar2)) &&
        (bVar2 = ::out(param_1,&this->exact,1,"exact"), bVar2)) &&
       (((bVar2 = ::out(param_1,(long64 *)&local_c,8,"whatClass"), bVar2 &&
         (bVar2 = ::out(param_1,&this->isInTransition,1,"isInTransition"), bVar2)) &&
        ((bVar2 = ::out(param_1,&this->wasInTransition,1,"wasInTransition"), bVar2 &&
         ((bVar2 = ::out(param_1,&this->waitStart,4,"waitStart"), bVar2 &&
          (bVar2 = ::out(param_1,&this->waitDeploy,1,"waitDeploy"), bVar2)))))))))) &&
     ((bVar2 = ::out(param_1,&this->waitDeployTime,4,"waitDeployTime"), bVar2 &&
      ((bVar2 = ::out(param_1,&this->timeOut,4,"timeOut"), bVar2 &&
       (bVar2 = AiProcess::Save((AiProcess *)this,param_1), bVar2)))))) {
    return true;
  }
  return false;
}
