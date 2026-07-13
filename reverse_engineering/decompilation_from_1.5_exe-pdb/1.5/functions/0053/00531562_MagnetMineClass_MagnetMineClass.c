/*
 * Entry: 00531562
 * Name: MagnetMineClass::MagnetMineClass
 * Namespace: MagnetMineClass
 * Signature: MagnetMineClass * MagnetMineClass(MagnetMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MagnetMineClass * __thiscall MagnetMineClass::MagnetMineClass(MagnetMineClass *this)

{
  MineClass::MineClass((MineClass *)this);
  this->_padding_ = 0x42700000;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x4d474e54;
  this->triggerDelay = 2.0;
  this->_padding_ = (int)"magnet";
  this->fieldRadius = 20.0;
  this->objPushCenter = 30.0;
  this->objPushEdge = 3.0;
  this->objDrag = 0.3;
  this->ordPushCenter = 100.0;
  this->ordPushEdge = 10.0;
  this->ordDrag = 1.0;
  return this;
}
