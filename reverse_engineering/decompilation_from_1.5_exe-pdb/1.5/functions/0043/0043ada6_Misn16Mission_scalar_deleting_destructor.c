/*
 * Entry: 0043ada6
 * Name: Misn16Mission::`scalar_deleting_destructor'
 * Namespace: Misn16Mission
 * Signature: void * `scalar_deleting_destructor'(Misn16Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn16Mission::_scalar_deleting_destructor_(Misn16Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
