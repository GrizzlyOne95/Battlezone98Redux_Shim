/*
 * Entry: 0053c298
 * Name: ThermalMissileClass::ThermalMissileClass
 * Namespace: ThermalMissileClass
 * Signature: ThermalMissileClass * ThermalMissileClass(ThermalMissileClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ThermalMissileClass * __thiscall ThermalMissileClass::ThermalMissileClass(ThermalMissileClass *this)

{
  MissileClass::MissileClass((MissileClass *)this);
  this->_padding_ = 0x3f800000;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x54484d4d;
  this->_padding_ = 0x42c80000;
  this->_padding_ = (int)"thermalmissile";
  this->_padding_ = 10;
  this->coneAngle = 0.31415927;
  return this;
}
