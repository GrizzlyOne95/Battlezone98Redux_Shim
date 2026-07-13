/*
 * Entry: 0053a309
 * Name: SpecialItemClass::~SpecialItemClass
 * Namespace: SpecialItemClass
 * Signature: void ~SpecialItemClass(SpecialItemClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpecialItemClass::~SpecialItemClass(SpecialItemClass *this)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  return;
}
