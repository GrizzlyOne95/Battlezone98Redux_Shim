/*
 * Entry: 0046dade
 * Name: UnitTask::UnitTask
 * Namespace: UnitTask
 * Signature: UnitTask * UnitTask(UnitTask * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnitTask * __thiscall UnitTask::UnitTask(UnitTask *this,Craft *param_1,GameObject *param_2)

{
  int iVar1;
  
  AiTask::AiTask((AiTask *)this);
  this->_padding_ = (int)&_vftable_;
  this->me = param_1;
  this->_padding_ = (int)param_1;
  if (param_2 == (GameObject *)0x0) {
    this->himHandle = 0;
  }
  else {
    iVar1 = GameObject::GetHandle(param_2);
    this->himHandle = iVar1;
  }
  this->nextState = -1;
  this->saveHandle = 0;
  (this->gotoPoint).x = 0.0;
  (this->gotoPoint).y = 0.0;
  (this->gotoPoint).z = 0.0;
  (this->goalPoint).x = 0.0;
  (this->goalPoint).y = 0.0;
  (this->goalPoint).z = 0.0;
  (this->gotoForce).x = 0.0;
  (this->gotoForce).y = 0.0;
  (this->gotoForce).z = 0.0;
  (this->gotoDir).x = 0.0;
  this->braccelFactor = 0.05;
  this->strafeFactor = 0.05;
  this->steerFactor = 3.0;
  (this->gotoDir).y = 0.0;
  this->omegaFactor = 0.2;
  this->omegaScale = 0.3;
  (this->gotoDir).z = 0.0;
  this->nextStuck = 0.0;
  this->skill = 0.0;
  (this->lastStuck).x = 0.0;
  this->rangeSq = 0.0;
  this->time = 0.0;
  this->shotSpeed = 0.0;
  this->shotSpeedInv = 0.0;
  (this->lastStuck).y = 0.0;
  this->pitch = 0.0;
  (this->lastStuck).z = 0.0;
  this->curState = 0xd;
  this->saveState = 0xd;
  this->specialSlot = -1;
  this->wasInTransition = false;
  this->plan = (AiPath *)0x0;
  this->planPoint = 0;
  this->fixPoint = 0;
  this->avoidSkip = 0;
  this->avoidObj = (GameObject *)0x0;
  this->skipObj = (GameObject *)0x0;
  this->stuckState = 0;
  this->weapon = (Weapon *)0x0;
  this->special = (Weapon *)0x0;
  this->weaponCheck = 0;
  this->ableToHit = false;
  this->targetDistSq = 0.0;
  (this->targetDiff).x = 0.0;
  (this->targetDiff).y = 0.0;
  (this->targetDiff).z = 0.0;
  (this->targetDir).x = 0.0;
  (this->targetDir).y = 0.0;
  (this->targetDir).z = 0.0;
  (this->targetVel).x = 0.0;
  this->blastDist = 75.0;
  this->fireConeX = 0.0;
  this->fireConeY = 0.0;
  (this->targetVel).y = 0.0;
  (this->targetVel).z = 0.0;
  this->switchDist = SWITCH_TO_NEXT_POINT_DISTANCE;
  this->attackStart = 0.0;
  this->noHitTime = 0.0;
  this->followDx = 0.0;
  this->attackGroup = (AttackGroup *)0x0;
  this->followDz = 0.0;
  this->followGroup = (FollowGroup *)0x0;
  this->lastStopped = 0.0;
  this->threatOrd = (Ordnance *)0x0;
  this->timeOut = 0.0;
  (this->evadeForce).x = 0.0;
  (this->evadeForce).y = 0.0;
  (this->evadeForce).z = 0.0;
  Init(this);
  return this;
}
