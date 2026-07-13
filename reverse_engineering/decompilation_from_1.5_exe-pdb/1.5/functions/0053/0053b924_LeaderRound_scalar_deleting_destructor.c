/*
 * Entry: 0053b924
 * Name: LeaderRound::`scalar_deleting_destructor'
 * Namespace: LeaderRound
 * Signature: void * `scalar_deleting_destructor'(LeaderRound * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall LeaderRound::_scalar_deleting_destructor_(LeaderRound *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Rocket::~Rocket((Rocket *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
