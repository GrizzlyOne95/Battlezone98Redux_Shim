/*
 * Entry: 00401758
 * Name: stdext::exception::`scalar_deleting_destructor'
 * Namespace: stdext::exception
 * Signature: void * `scalar_deleting_destructor'(exception * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall stdext::exception::_scalar_deleting_destructor_(exception *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
