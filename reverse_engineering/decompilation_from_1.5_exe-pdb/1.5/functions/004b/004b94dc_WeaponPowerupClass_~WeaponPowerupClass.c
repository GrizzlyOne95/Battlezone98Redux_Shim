/*
 * Entry: 004b94dc
 * Name: WeaponPowerupClass::~WeaponPowerupClass
 * Namespace: WeaponPowerupClass
 * Signature: void ~WeaponPowerupClass(WeaponPowerupClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponPowerupClass::~WeaponPowerupClass(WeaponPowerupClass *this)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  return;
}
