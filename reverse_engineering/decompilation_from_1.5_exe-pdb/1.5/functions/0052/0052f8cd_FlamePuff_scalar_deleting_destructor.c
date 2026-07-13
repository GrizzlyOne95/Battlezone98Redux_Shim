/*
 * Entry: 0052f8cd
 * Name: FlamePuff::`scalar_deleting_destructor'
 * Namespace: FlamePuff
 * Signature: void * `scalar_deleting_destructor'(FlamePuff * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FlamePuff::_scalar_deleting_destructor_(FlamePuff *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
