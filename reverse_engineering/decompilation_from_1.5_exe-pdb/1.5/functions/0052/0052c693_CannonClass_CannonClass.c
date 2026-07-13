/*
 * Entry: 0052c693
 * Name: CannonClass::CannonClass
 * Namespace: CannonClass
 * Signature: CannonClass * CannonClass(CannonClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CannonClass * __thiscall CannonClass::CannonClass(CannonClass *this)

{
  WeaponClass::WeaponClass((WeaponClass *)this);
  this->shotDelay = 0.2;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x43414e4e;
  this->_padding_ = (int)"cannon";
  strncpy((char *)&this->_padding_,"h45ch.wav",0x10);
  return this;
}
