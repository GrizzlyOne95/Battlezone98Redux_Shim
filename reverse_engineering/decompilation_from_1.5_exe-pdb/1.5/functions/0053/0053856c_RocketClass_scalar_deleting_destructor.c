/*
 * Entry: 0053856c
 * Name: RocketClass::`scalar_deleting_destructor'
 * Namespace: RocketClass
 * Signature: void * `scalar_deleting_destructor'(RocketClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RocketClass::_scalar_deleting_destructor_(RocketClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
