/*
 * Entry: 004b48e8
 * Name: TurretCraftClass::TurretCraftClass
 * Namespace: TurretCraftClass
 * Signature: TurretCraftClass * TurretCraftClass(TurretCraftClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretCraftClass * __thiscall TurretCraftClass::TurretCraftClass(TurretCraftClass *this)

{
  CraftClass::CraftClass((CraftClass *)this);
  this->_padding_ = 0;
  this->omegaTurret = 2.0;
  this->_padding_ = (int)&_vftable_;
  this->alphaTrack = 10.0;
  this->_padding_ = 0x54555252;
  this->_padding_ = (int)"turret";
  this->alphaDamp = 3.0;
  this->_padding_ = 6;
  this->_padding_ = 0x50;
  this->pitchPitch = 0.2;
  this->_padding_ = 0x59;
  return this;
}
