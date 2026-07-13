/*
 * Entry: 00532239
 * Name: MissileClass::MissileClass
 * Namespace: MissileClass
 * Signature: MissileClass * MissileClass(MissileClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MissileClass * __thiscall MissileClass::MissileClass(MissileClass *this)

{
  RocketClass::RocketClass((RocketClass *)this);
  this->omegaTurn = 1.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x4d53534c;
  this->shotAccel = 100.0;
  this->_padding_ = (int)"missile";
  *(undefined1 *)((int)&this->_padding_ + 2) = 1;
  this->_padding_ = 10;
  return this;
}
