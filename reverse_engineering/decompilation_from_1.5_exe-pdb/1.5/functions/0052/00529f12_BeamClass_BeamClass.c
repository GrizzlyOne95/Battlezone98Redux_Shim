/*
 * Entry: 00529f12
 * Name: BeamClass::BeamClass
 * Namespace: BeamClass
 * Signature: BeamClass * BeamClass(BeamClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BeamClass * __thiscall BeamClass::BeamClass(BeamClass *this)

{
  BulletClass::BulletClass((BulletClass *)this);
  this->_padding_ = 0x3951b717;
  this->_padding_ = 0x49742400;
  *(undefined2 *)&this->_padding_ = 1;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x42c80000;
  this->_padding_ = 0x4245414d;
  this->_padding_ = (int)"beam";
  this->segmentRadius = 0.1;
  this->_padding_ = 10;
  this->segmentLength = 2.0;
  this->segmentVariance = 2.0;
  return this;
}
