/*
 * Entry: 0053853b
 * Name: RocketClass::~RocketClass
 * Namespace: RocketClass
 * Signature: void ~RocketClass(RocketClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketClass::~RocketClass(RocketClass *this)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  return;
}
