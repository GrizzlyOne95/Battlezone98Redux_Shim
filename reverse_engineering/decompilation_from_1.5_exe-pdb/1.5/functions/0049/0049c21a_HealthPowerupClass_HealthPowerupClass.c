/*
 * Entry: 0049c21a
 * Name: HealthPowerupClass::HealthPowerupClass
 * Namespace: HealthPowerupClass
 * Signature: HealthPowerupClass * HealthPowerupClass(HealthPowerupClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HealthPowerupClass * __thiscall HealthPowerupClass::HealthPowerupClass(HealthPowerupClass *this)

{
  PowerUpClass::PowerUpClass((PowerUpClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x524b4954;
  this->_padding_ = (int)"repairkit";
  strncpy((char *)&this->_padding_,"repair.wav",0x10);
  this->healthUp = 1000;
  return this;
}
