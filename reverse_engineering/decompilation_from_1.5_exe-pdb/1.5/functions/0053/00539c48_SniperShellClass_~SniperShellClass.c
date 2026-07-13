/*
 * Entry: 00539c48
 * Name: SniperShellClass::~SniperShellClass
 * Namespace: SniperShellClass
 * Signature: void ~SniperShellClass(SniperShellClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperShellClass::~SniperShellClass(SniperShellClass *this)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  return;
}
