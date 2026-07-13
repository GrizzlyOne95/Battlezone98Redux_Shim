/*
 * Entry: 0052ad1f
 * Name: BoltClass::~BoltClass
 * Namespace: BoltClass
 * Signature: void ~BoltClass(BoltClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BoltClass::~BoltClass(BoltClass *this)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  return;
}
