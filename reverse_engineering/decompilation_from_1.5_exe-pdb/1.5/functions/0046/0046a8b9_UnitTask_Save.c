/*
 * Entry: 0046a8b9
 * Name: UnitTask::Save
 * Namespace: UnitTask
 * Signature: bool Save(UnitTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitTask::Save(UnitTask *this,_iobuf *param_1)

{
  bool bVar1;
  GameObject *local_c;
  GameObject *local_8;
  
  local_8 = (GameObject *)0x0;
  if (this->attackGroup != (AttackGroup *)0x0) {
    local_c = (GameObject *)this;
    local_8 = AttackGroup::GetTarget(this->attackGroup);
  }
  local_c = (GameObject *)0x0;
  if (this->followGroup != (FollowGroup *)0x0) {
    local_c = FollowGroup::GetLeader(this->followGroup);
  }
  bVar1 = ::out(param_1,&this->curState,4,"curState");
  if ((((((bVar1) && (bVar1 = ::out(param_1,&this->nextState,4,"nextState"), bVar1)) &&
        (bVar1 = out_ptr(param_1,&this->me,4,"me"), bVar1)) &&
       (((bVar1 = ::out(param_1,&this->himHandle,4,"himHandle"), bVar1 &&
         (bVar1 = ::out(param_1,&this->wasInTransition,1,"wasInTransition"), bVar1)) &&
        ((bVar1 = ::out(param_1,&this->saveState,4,"saveState"), bVar1 &&
         ((bVar1 = ::out(param_1,&this->saveHandle,4,"saveHandle"), bVar1 &&
          (bVar1 = ::out(param_1,&this->gotoPoint,0xc,"gotoPoint"), bVar1)))))))) &&
      ((bVar1 = out_ptr(param_1,&this->plan,4,"plan"), bVar1 &&
       (((bVar1 = ::out(param_1,&this->planPoint,4,"planPoint"), bVar1 &&
         (bVar1 = ::out(param_1,&this->braccelFactor,4,"braccelFactor"), bVar1)) &&
        (bVar1 = ::out(param_1,&this->steerFactor,4,"steerFactor"), bVar1)))))) &&
     (((((bVar1 = ::out(param_1,&this->strafeFactor,4,"strafeFactor"), bVar1 &&
         (bVar1 = ::out(param_1,&this->avoidSkip,4,"avoidSkip"), bVar1)) &&
        ((bVar1 = ::out(param_1,&this->nextStuck,4,"nextStuck"), bVar1 &&
         ((bVar1 = ::out(param_1,&this->lastStuck,0xc,"lastStuck"), bVar1 &&
          (bVar1 = ::out(param_1,&this->stuckState,4,"stuckState"), bVar1)))))) &&
       (bVar1 = ::out(param_1,&this->pitch,4,"pitch"), bVar1)) &&
      (((((bVar1 = ::out(param_1,&this->blastDist,4,"blastDist"), bVar1 &&
          (bVar1 = ::out(param_1,&this->fireConeX,4,"fireConeX"), bVar1)) &&
         (bVar1 = ::out(param_1,&this->fireConeY,4,"fireConeY"), bVar1)) &&
        ((bVar1 = ::out(param_1,&this->switchDist,4,"switchDist"), bVar1 &&
         (bVar1 = ::out(param_1,&this->attackStart,4,"attackStart"), bVar1)))) &&
       ((((bVar1 = out_ptr(param_1,&local_8,4,"attackTarget"), bVar1 &&
          ((bVar1 = ::out(param_1,&this->noHitTime,4,"noHitTime"), bVar1 &&
           (bVar1 = ::out(param_1,&this->followDx,4,"followDx"), bVar1)))) &&
         (bVar1 = ::out(param_1,&this->followDz,4,"followDz"), bVar1)) &&
        ((((bVar1 = ::out(param_1,&this->lastStopped,4,"lastStopped"), bVar1 &&
           (bVar1 = out_ptr(param_1,&local_c,4,"followTarget"), bVar1)) &&
          (bVar1 = ::out(param_1,&this->timeOut,4,"timeOut"), bVar1)) &&
         (bVar1 = AiTask::Save((AiTask *)this,param_1), bVar1)))))))))) {
    return true;
  }
  return false;
}
