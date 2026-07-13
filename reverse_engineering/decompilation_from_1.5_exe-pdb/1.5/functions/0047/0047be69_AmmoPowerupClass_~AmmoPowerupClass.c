/*
 * Entry: 0047be69
 * Name: AmmoPowerupClass::~AmmoPowerupClass
 * Namespace: AmmoPowerupClass
 * Signature: void ~AmmoPowerupClass(AmmoPowerupClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AmmoPowerupClass::~AmmoPowerupClass(AmmoPowerupClass *this)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  return;
}
