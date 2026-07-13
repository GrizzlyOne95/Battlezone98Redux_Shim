/*
 * Entry: 0052f784
 * Name: FlamePuffClass::`scalar_deleting_destructor'
 * Namespace: FlamePuffClass
 * Signature: void * `scalar_deleting_destructor'(FlamePuffClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FlamePuffClass::_scalar_deleting_destructor_(FlamePuffClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
