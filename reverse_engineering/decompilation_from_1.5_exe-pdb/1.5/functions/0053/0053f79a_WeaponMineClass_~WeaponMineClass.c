/*
 * Entry: 0053f79a
 * Name: WeaponMineClass::~WeaponMineClass
 * Namespace: WeaponMineClass
 * Signature: void ~WeaponMineClass(WeaponMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponMineClass::~WeaponMineClass(WeaponMineClass *this)

{
  this->_padding_ = (int)&_vftable_;
  MineClass::~MineClass((MineClass *)this);
  return;
}
