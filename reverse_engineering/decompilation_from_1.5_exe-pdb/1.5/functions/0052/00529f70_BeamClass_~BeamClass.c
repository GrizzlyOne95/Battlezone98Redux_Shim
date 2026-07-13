/*
 * Entry: 00529f70
 * Name: BeamClass::~BeamClass
 * Namespace: BeamClass
 * Signature: void ~BeamClass(BeamClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BeamClass::~BeamClass(BeamClass *this)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  return;
}
