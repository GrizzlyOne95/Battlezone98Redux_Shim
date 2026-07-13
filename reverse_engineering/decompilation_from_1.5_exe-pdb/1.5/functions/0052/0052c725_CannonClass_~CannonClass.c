/*
 * Entry: 0052c725
 * Name: CannonClass::~CannonClass
 * Namespace: CannonClass
 * Signature: void ~CannonClass(CannonClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CannonClass::~CannonClass(CannonClass *this)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  return;
}
