/*
 * Entry: 0047bdd1
 * Name: AmmoPowerupClass::AmmoPowerupClass
 * Namespace: AmmoPowerupClass
 * Signature: AmmoPowerupClass * AmmoPowerupClass(AmmoPowerupClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AmmoPowerupClass * __thiscall AmmoPowerupClass::AmmoPowerupClass(AmmoPowerupClass *this)

{
  PowerUpClass::PowerUpClass((PowerUpClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x414d4d4f;
  this->_padding_ = (int)"ammopack";
  strncpy((char *)&this->_padding_,"weapon.wav",0x10);
  this->ammoUp = 500;
  return this;
}
