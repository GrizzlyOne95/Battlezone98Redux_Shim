/*
 * Entry: 0053b075
 * Name: TargetingGun::~TargetingGun
 * Namespace: TargetingGun
 * Signature: void ~TargetingGun(TargetingGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TargetingGun::~TargetingGun(TargetingGun *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->leaderObj != (LeaderRound *)0x0) {
    this->leaderObj->launcherObj = (TargetingGun *)0x0;
  }
  Weapon::~Weapon((Weapon *)this);
  return;
}
