/*
 * Entry: 0053bb79
 * Name: TeamSwitcherClass::`scalar_deleting_destructor'
 * Namespace: TeamSwitcherClass
 * Signature: void * `scalar_deleting_destructor'(TeamSwitcherClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
TeamSwitcherClass::_scalar_deleting_destructor_(TeamSwitcherClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
