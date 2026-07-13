/*
 * Entry: 0053d9e9
 * Name: TracerClass::~TracerClass
 * Namespace: TracerClass
 * Signature: void ~TracerClass(TracerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TracerClass::~TracerClass(TracerClass *this)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  return;
}
