/*
 * Entry: 0043d526
 * Name: Misn17Mission::`scalar_deleting_destructor'
 * Namespace: Misn17Mission
 * Signature: void * `scalar_deleting_destructor'(Misn17Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn17Mission::_scalar_deleting_destructor_(Misn17Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
