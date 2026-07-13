/*
 * Entry: 004b69f5
 * Name: TurretTankClass::TurretTankClass
 * Namespace: TurretTankClass
 * Signature: TurretTankClass * TurretTankClass(TurretTankClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretTankClass * __thiscall TurretTankClass::TurretTankClass(TurretTankClass *this)

{
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  this->timeUndeploy = 2.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x54544e4b;
  *(undefined4 *)&this->field_0x3c4 = 0x40a00000;
  this->_padding_ = (int)"turrettank";
  this[1]._padding_ = 0x40a00000;
  this->_padding_ = 0xf;
  this->_padding_ = 0x18;
  return this;
}
