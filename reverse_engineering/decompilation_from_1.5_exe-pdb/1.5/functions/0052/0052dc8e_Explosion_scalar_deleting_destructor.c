/*
 * Entry: 0052dc8e
 * Name: Explosion::`scalar_deleting_destructor'
 * Namespace: Explosion
 * Signature: void * `scalar_deleting_destructor'(Explosion * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Explosion::_scalar_deleting_destructor_(Explosion *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
