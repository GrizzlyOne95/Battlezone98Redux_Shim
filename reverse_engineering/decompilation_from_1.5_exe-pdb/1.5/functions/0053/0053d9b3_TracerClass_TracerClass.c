/*
 * Entry: 0053d9b3
 * Name: TracerClass::TracerClass
 * Namespace: TracerClass
 * Signature: TracerClass * TracerClass(TracerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TracerClass * __thiscall TracerClass::TracerClass(TracerClass *this)

{
  BulletClass::BulletClass((BulletClass *)this);
  this->tracerIndex = 0;
  this->lodShift = 0.0;
  this->shotColor = 0;
  this->tracerLength = 0.0;
  this->tracerRadius = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x54524143;
  this->_padding_ = (int)"tracer";
  return this;
}
