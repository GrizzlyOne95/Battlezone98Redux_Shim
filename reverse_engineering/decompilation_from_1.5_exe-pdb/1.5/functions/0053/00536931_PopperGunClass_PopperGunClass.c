/*
 * Entry: 00536931
 * Name: PopperGunClass::PopperGunClass
 * Namespace: PopperGunClass
 * Signature: PopperGunClass * PopperGunClass(PopperGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PopperGunClass * __thiscall PopperGunClass::PopperGunClass(PopperGunClass *this)

{
  WeaponClass::WeaponClass((WeaponClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x504f5047;
  this->_padding_ = (int)"poppergun";
  strncpy((char *)&this->_padding_,"wcbl.wav",0x10);
  this->shotDelay = 1.0;
  this->fireAngle = 1.0;
  return this;
}
