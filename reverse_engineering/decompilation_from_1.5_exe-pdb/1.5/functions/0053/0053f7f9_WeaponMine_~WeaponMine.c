/*
 * Entry: 0053f7f9
 * Name: WeaponMine::~WeaponMine
 * Namespace: WeaponMine
 * Signature: void ~WeaponMine(WeaponMine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponMine::~WeaponMine(WeaponMine *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Mine::~Mine((Mine *)this);
  return;
}
