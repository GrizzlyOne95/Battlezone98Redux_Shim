/*
 * Entry: 0053afae
 * Name: TargetingGunClass::~TargetingGunClass
 * Namespace: TargetingGunClass
 * Signature: void ~TargetingGunClass(TargetingGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TargetingGunClass::~TargetingGunClass(TargetingGunClass *this)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  return;
}
