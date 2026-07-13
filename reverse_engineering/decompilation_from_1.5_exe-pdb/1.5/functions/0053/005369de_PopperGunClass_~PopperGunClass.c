/*
 * Entry: 005369de
 * Name: PopperGunClass::~PopperGunClass
 * Namespace: PopperGunClass
 * Signature: void ~PopperGunClass(PopperGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PopperGunClass::~PopperGunClass(PopperGunClass *this)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  return;
}
