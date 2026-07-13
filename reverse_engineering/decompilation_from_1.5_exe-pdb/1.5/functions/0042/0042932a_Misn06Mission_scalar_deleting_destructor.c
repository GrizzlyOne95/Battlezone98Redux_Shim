/*
 * Entry: 0042932a
 * Name: Misn06Mission::`scalar_deleting_destructor'
 * Namespace: Misn06Mission
 * Signature: void * `scalar_deleting_destructor'(Misn06Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn06Mission::_scalar_deleting_destructor_(Misn06Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
