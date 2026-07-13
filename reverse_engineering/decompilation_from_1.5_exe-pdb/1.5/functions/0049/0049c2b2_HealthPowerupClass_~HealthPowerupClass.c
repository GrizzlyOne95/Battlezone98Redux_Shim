/*
 * Entry: 0049c2b2
 * Name: HealthPowerupClass::~HealthPowerupClass
 * Namespace: HealthPowerupClass
 * Signature: void ~HealthPowerupClass(HealthPowerupClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HealthPowerupClass::~HealthPowerupClass(HealthPowerupClass *this)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  return;
}
