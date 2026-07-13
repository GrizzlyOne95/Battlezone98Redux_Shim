/*
 * Entry: 0046a4ee
 * Name: UnitTask::Load
 * Namespace: UnitTask
 * Signature: bool Load(UnitTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitTask::Load(UnitTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->curState,4);
  if (((((bVar1) && (bVar1 = ::in(param_1,&this->nextState,4), bVar1)) &&
       (bVar1 = in_ptr(param_1,&this->me,4,"me",this), bVar1)) &&
      (((bVar1 = ::in(param_1,&this->himHandle,4), bVar1 &&
        (bVar1 = ::in(param_1,&this->wasInTransition,1), bVar1)) &&
       ((bVar1 = ::in(param_1,&this->saveState,4), bVar1 &&
        ((bVar1 = ::in(param_1,&this->saveHandle,4), bVar1 &&
         (bVar1 = ::in(param_1,&this->gotoPoint,0xc), bVar1)))))))) &&
     ((bVar1 = in_ptr(param_1,&this->plan,4,"plan",this), bVar1 &&
      ((((bVar1 = ::in(param_1,&this->planPoint,4), bVar1 &&
         (bVar1 = ::in(param_1,&this->braccelFactor,4), bVar1)) &&
        (bVar1 = ::in(param_1,&this->steerFactor,4), bVar1)) &&
       ((bVar1 = ::in(param_1,&this->strafeFactor,4), bVar1 &&
        (bVar1 = ::in(param_1,&this->avoidSkip,4), bVar1)))))))) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (0x40e < version) {
    if ((bVar1) && (bVar1 = ::in(param_1,&this->nextStuck,4), bVar1)) goto LAB_0046a655;
    bVar1 = false;
  }
  if (!bVar1) {
    return false;
  }
LAB_0046a655:
  bVar1 = ::in(param_1,&this->lastStuck,0xc);
  if (((((bVar1) && (bVar1 = ::in(param_1,&this->stuckState,4), bVar1)) &&
       (bVar1 = ::in(param_1,&this->pitch,4), bVar1)) &&
      (((((bVar1 = ::in(param_1,&this->blastDist,4), bVar1 &&
          (bVar1 = ::in(param_1,&this->fireConeX,4), bVar1)) &&
         ((bVar1 = ::in(param_1,&this->fireConeY,4), bVar1 &&
          ((bVar1 = ::in(param_1,&this->switchDist,4), bVar1 &&
           (bVar1 = ::in(param_1,&this->attackStart,4), bVar1)))))) &&
        (bVar1 = in_ptr(param_1,&this->attackGroup,4,"attackTarget",this), bVar1)) &&
       ((((bVar1 = ::in(param_1,&this->noHitTime,4), bVar1 &&
          (bVar1 = ::in(param_1,&this->followDx,4), bVar1)) &&
         (bVar1 = ::in(param_1,&this->followDz,4), bVar1)) &&
        ((bVar1 = ::in(param_1,&this->lastStopped,4), bVar1 &&
         (bVar1 = in_ptr(param_1,&this->followGroup,4,"followTarget",this), bVar1)))))))) &&
     ((bVar1 = ::in(param_1,&this->timeOut,4), bVar1 &&
      (bVar1 = AiTask::Load((AiTask *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
