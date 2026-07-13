/*
 * Entry: 0053bbc1
 * Name: TeamSwitcher::`scalar_deleting_destructor'
 * Namespace: TeamSwitcher
 * Signature: void * `scalar_deleting_destructor'(TeamSwitcher * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TeamSwitcher::_scalar_deleting_destructor_(TeamSwitcher *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Rocket::~Rocket((Rocket *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
