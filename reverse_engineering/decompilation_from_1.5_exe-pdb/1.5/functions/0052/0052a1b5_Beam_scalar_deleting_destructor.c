/*
 * Entry: 0052a1b5
 * Name: Beam::`scalar_deleting_destructor'
 * Namespace: Beam
 * Signature: void * `scalar_deleting_destructor'(Beam * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Beam::_scalar_deleting_destructor_(Beam *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
