/*
 * Entry: 0052aef8
 * Name: Bolt::`scalar_deleting_destructor'
 * Namespace: Bolt
 * Signature: void * `scalar_deleting_destructor'(Bolt * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Bolt::_scalar_deleting_destructor_(Bolt *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
