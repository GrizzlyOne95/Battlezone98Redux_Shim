/*
 * Entry: 0053af31
 * Name: TargetingGunClass::TargetingGunClass
 * Namespace: TargetingGunClass
 * Signature: TargetingGunClass * TargetingGunClass(TargetingGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TargetingGunClass * __thiscall TargetingGunClass::TargetingGunClass(TargetingGunClass *this)

{
  WeaponClass::WeaponClass((WeaponClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x54524754;
  this->_padding_ = (int)"targeting";
  strncpy((char *)&this->_padding_,"whmgun.wav",0x10);
  strncpy(this->leaderSound,"h45ch.wav",0x10);
  this->shotDelay = 1.0;
  this->firstDelay = 1.0;
  this->leaderClass = (OrdnanceClass *)0x0;
  this->lockingReticle = 0;
  this->salvoDelay = 0.2;
  this->lockedReticle = 0;
  this->salvoCount = 10;
  return this;
}
