/*
 * Entry: 0053b3ac
 * Name: TargetingGun::TargetingGun
 * Namespace: TargetingGun
 * Signature: TargetingGun * TargetingGun(TargetingGun * this, _OBJ76 * param_1, TargetingGunClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TargetingGun * __thiscall
TargetingGun::TargetingGun(TargetingGun *this,_OBJ76 *param_1,TargetingGunClass *param_2)

{
  OrdnanceClass *pOVar1;
  GameObject *pGVar2;
  
  Weapon::Weapon((Weapon *)this,param_1,(WeaponClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  this->go = (_gas_object *)0x0;
  pOVar1 = param_2->leaderClass;
  this->shotTimer = 0.0;
  this->leaderClass = pOVar1;
  this->salvoCount = 0;
  if (this->_padding_ == 0) {
    pGVar2 = (GameObject *)0x0;
  }
  else {
    pGVar2 = *(GameObject **)(this->_padding_ + 0xb4);
  }
  this->carrier = pGVar2;
  this->triggered = false;
  this->lockTarget = (GameObject *)0x0;
  this->leaderObj = (LeaderRound *)0x0;
  return this;
}
