/*
 * Entry: 0052d6a4
 * Name: DispenserClass::~DispenserClass
 * Namespace: DispenserClass
 * Signature: void ~DispenserClass(DispenserClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DispenserClass::~DispenserClass(DispenserClass *this)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  return;
}
