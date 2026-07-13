/*
 * Entry: 004b9405
 * Name: WeaponPowerupClass::WeaponPowerupClass
 * Namespace: WeaponPowerupClass
 * Signature: WeaponPowerupClass * WeaponPowerupClass(WeaponPowerupClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponPowerupClass * __thiscall WeaponPowerupClass::WeaponPowerupClass(WeaponPowerupClass *this)

{
  PowerUpClass::PowerUpClass((PowerUpClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x5745504e;
  this->_padding_ = (int)"wpnpower";
  strncpy((char *)&this->_padding_,"weapon.wav",0x10);
  this->weaponClass = (WeaponClass *)0x0;
  return this;
}
