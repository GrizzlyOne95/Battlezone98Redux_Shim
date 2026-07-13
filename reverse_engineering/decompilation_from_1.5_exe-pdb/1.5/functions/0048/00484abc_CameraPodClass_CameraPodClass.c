/*
 * Entry: 00484abc
 * Name: CameraPodClass::CameraPodClass
 * Namespace: CameraPodClass
 * Signature: CameraPodClass * CameraPodClass(CameraPodClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CameraPodClass * __thiscall CameraPodClass::CameraPodClass(CameraPodClass *this)

{
  PowerUpClass::PowerUpClass((PowerUpClass *)this);
  this->omegaSpin = 1.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x43504f44;
  this->rangeScan = 200.0;
  this->_padding_ = (int)"camerapod";
  this->_padding_ = 0x23;
  this->periodScan = 0.0;
  this->_padding_ = 0x2c;
  return this;
}
