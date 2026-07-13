/*
 * Entry: 00539cab
 * Name: SniperShellClass::`scalar_deleting_destructor'
 * Namespace: SniperShellClass
 * Signature: void * `scalar_deleting_destructor'(SniperShellClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SniperShellClass::_scalar_deleting_destructor_(SniperShellClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
