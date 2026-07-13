/*
 * Entry: 0053b364
 * Name: LeaderRoundClass::`scalar_deleting_destructor'
 * Namespace: LeaderRoundClass
 * Signature: void * `scalar_deleting_destructor'(LeaderRoundClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
LeaderRoundClass::_scalar_deleting_destructor_(LeaderRoundClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
