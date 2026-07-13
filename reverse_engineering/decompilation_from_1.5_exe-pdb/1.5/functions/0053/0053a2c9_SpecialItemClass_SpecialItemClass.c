/*
 * Entry: 0053a2c9
 * Name: SpecialItemClass::SpecialItemClass
 * Namespace: SpecialItemClass
 * Signature: SpecialItemClass * SpecialItemClass(SpecialItemClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpecialItemClass * __thiscall SpecialItemClass::SpecialItemClass(SpecialItemClass *this)

{
  WeaponClass::WeaponClass((WeaponClass *)this);
  this->triggerDelay = 1.0;
  this->activeSound[0] = '\0';
  this->expireSound[0] = '\0';
  this->reticleCount = 0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x5350434c;
  this->_padding_ = (int)"specialitem";
  this->ammoCost = 100;
  return this;
}
