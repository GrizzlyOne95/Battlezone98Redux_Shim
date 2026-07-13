/*
 * Entry: 0052cc25
 * Name: ChargeGunClass::ChargeGunClass
 * Namespace: ChargeGunClass
 * Signature: ChargeGunClass * ChargeGunClass(ChargeGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ChargeGunClass * __thiscall ChargeGunClass::ChargeGunClass(ChargeGunClass *this)

{
  CannonClass::CannonClass((CannonClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x43485247;
  this->_padding_ = (int)"chargegun";
  strncpy((char *)&this->_padding_,"wlflame.wav",0x10);
  this->ordnanceData = (OrdnanceData *)0x0;
  this->startRate = 11025.0;
  this->deltaRate = 4000.0;
  this->ordnanceCount = 1;
  this->startVolume = 100.0;
  this->deltaVolume = 0.0;
  return this;
}
