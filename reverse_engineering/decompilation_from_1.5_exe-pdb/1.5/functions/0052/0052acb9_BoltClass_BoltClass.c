/*
 * Entry: 0052acb9
 * Name: BoltClass::BoltClass
 * Namespace: BoltClass
 * Signature: BoltClass * BoltClass(BoltClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BoltClass * __thiscall BoltClass::BoltClass(BoltClass *this)

{
  BulletClass::BulletClass((BulletClass *)this);
  this->_padding_ = 0x3f800000;
  this->_padding_ = 0x42c80000;
  *(undefined2 *)&this->_padding_ = 1;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x43480000;
  this->_padding_ = 0x424f4c54;
  this->_padding_ = (int)"bolt";
  this->segmentRadius = 0.1;
  this->_padding_ = 10;
  this->segmentLength = 2.0;
  this->segmentVariance = 0.5;
  this->effectDuration = 0.1;
  return this;
}
