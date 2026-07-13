/*
 * Entry: 00529c90
 * Name: AnchorRocketClass::`scalar_deleting_destructor'
 * Namespace: AnchorRocketClass
 * Signature: void * `scalar_deleting_destructor'(AnchorRocketClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
AnchorRocketClass::_scalar_deleting_destructor_(AnchorRocketClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
