/*
 * Entry: 004209b7
 * Name: Misn03Mission::`scalar_deleting_destructor'
 * Namespace: Misn03Mission
 * Signature: void * `scalar_deleting_destructor'(Misn03Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn03Mission::_scalar_deleting_destructor_(Misn03Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
