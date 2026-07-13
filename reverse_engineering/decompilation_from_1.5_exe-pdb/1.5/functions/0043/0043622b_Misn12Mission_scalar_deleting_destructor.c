/*
 * Entry: 0043622b
 * Name: Misn12Mission::`scalar_deleting_destructor'
 * Namespace: Misn12Mission
 * Signature: void * `scalar_deleting_destructor'(Misn12Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn12Mission::_scalar_deleting_destructor_(Misn12Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
