/*
 * Entry: 00450050
 * Name: Strip::`scalar_deleting_destructor'
 * Namespace: Strip
 * Signature: void * `scalar_deleting_destructor'(Strip * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Strip::_scalar_deleting_destructor_(Strip *this,uint param_1)

{
  pathMem = pathMem + -0x3c;
  this->_padding_ = (int)&_vftable_;
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
