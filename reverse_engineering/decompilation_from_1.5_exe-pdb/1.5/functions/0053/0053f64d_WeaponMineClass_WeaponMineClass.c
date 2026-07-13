/*
 * Entry: 0053f64d
 * Name: WeaponMineClass::WeaponMineClass
 * Namespace: WeaponMineClass
 * Signature: WeaponMineClass * WeaponMineClass(WeaponMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponMineClass * __thiscall WeaponMineClass::WeaponMineClass(WeaponMineClass *this)

{
  MineClass::MineClass((MineClass *)this);
  this->weaponClass = (WeaponClass *)0x0;
  this->_padding_ = 0x7149f2ca;
  this->_padding_ = (int)&_vftable_;
  this->searchRadius = 50.0;
  this->_padding_ = 0x57504e4d;
  this->_padding_ = (int)"weaponmine";
  this->heightScale = 10.0;
  this->_padding_ = 1000;
  this->checkSight = false;
  return this;
}
