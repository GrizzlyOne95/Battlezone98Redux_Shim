/*
 * Entry: 0046b243
 * Name: UnitTask::UnitTask
 * Namespace: UnitTask
 * Signature: UnitTask * UnitTask(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnitTask * __thiscall UnitTask::UnitTask(UnitTask *this)

{
  AiTask::AiTask((AiTask *)this);
  (this->gotoPoint).x = 0.0;
  (this->gotoPoint).y = 0.0;
  (this->gotoPoint).z = 0.0;
  (this->goalPoint).x = 0.0;
  (this->goalPoint).y = 0.0;
  (this->goalPoint).z = 0.0;
  (this->gotoForce).x = 0.0;
  (this->gotoForce).y = 0.0;
  (this->gotoForce).z = 0.0;
  this->specialSlot = -1;
  this->braccelFactor = 0.0;
  this->strafeFactor = 0.0;
  (this->gotoDir).x = 0.0;
  this->steerFactor = 0.0;
  this->omegaFactor = 0.0;
  this->omegaScale = 0.0;
  this->nextStuck = 0.0;
  (this->gotoDir).y = 0.0;
  (this->gotoDir).z = 0.0;
  this->skill = 0.0;
  (this->lastStuck).x = 0.0;
  this->rangeSq = 0.0;
  this->time = 0.0;
  this->shotSpeed = 0.0;
  this->shotSpeedInv = 0.0;
  (this->lastStuck).y = 0.0;
  this->pitch = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->curState = 0xd;
  this->nextState = 0xd;
  this->me = (Craft *)0x0;
  this->himHandle = 0;
  this->him = (GameObject *)0x0;
  this->wasInTransition = false;
  this->saveState = 0xd;
  this->saveHandle = 0;
  this->plan = (AiPath *)0x0;
  this->planPoint = 0;
  this->fixPoint = 0;
  this->avoidSkip = 0;
  this->avoidObj = (GameObject *)0x0;
  this->skipObj = (GameObject *)0x0;
  (this->lastStuck).z = 0.0;
  this->stuckState = 0;
  this->weapon = (Weapon *)0x0;
  this->special = (Weapon *)0x0;
  this->weaponCheck = 0;
  (this->targetDiff).x = 0.0;
  this->targetDistSq = 0.0;
  (this->targetDiff).y = 0.0;
  (this->targetDiff).z = 0.0;
  (this->targetDir).x = 0.0;
  (this->targetDir).y = 0.0;
  (this->targetDir).z = 0.0;
  this->blastDist = 0.0;
  (this->targetVel).x = 0.0;
  this->fireConeX = 0.0;
  this->fireConeY = 0.0;
  this->switchDist = 0.0;
  this->attackStart = 0.0;
  (this->targetVel).y = 0.0;
  this->noHitTime = 0.0;
  this->followDx = 0.0;
  this->followDz = 0.0;
  this->lastStopped = 0.0;
  (this->targetVel).z = 0.0;
  this->timeOut = 0.0;
  (this->evadeForce).x = 0.0;
  (this->evadeForce).y = 0.0;
  (this->evadeForce).z = 0.0;
  this->ableToHit = false;
  this->attackGroup = (AttackGroup *)0x0;
  this->followGroup = (FollowGroup *)0x0;
  this->threatOrd = (Ordnance *)0x0;
  return this;
}
