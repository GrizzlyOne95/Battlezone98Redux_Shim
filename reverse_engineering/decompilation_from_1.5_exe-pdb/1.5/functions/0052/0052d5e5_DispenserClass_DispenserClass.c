/*
 * Entry: 0052d5e5
 * Name: DispenserClass::DispenserClass
 * Namespace: DispenserClass
 * Signature: DispenserClass * DispenserClass(DispenserClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DispenserClass * __thiscall DispenserClass::DispenserClass(DispenserClass *this)

{
  WeaponClass::WeaponClass((WeaponClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x44495350;
  this->_padding_ = (int)"dispenser";
  strncpy((char *)&this->_padding_,"wwgpl.wav",0x10);
  this->shotDelay = 1.0;
  return this;
}
