/*
 * Entry: 0053c33a
 * Name: ThermalMissileClass::~ThermalMissileClass
 * Namespace: ThermalMissileClass
 * Signature: void ~ThermalMissileClass(ThermalMissileClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ThermalMissileClass::~ThermalMissileClass(ThermalMissileClass *this)

{
  this->_padding_ = (int)&_vftable_;
  MissileClass::~MissileClass((MissileClass *)this);
  return;
}
