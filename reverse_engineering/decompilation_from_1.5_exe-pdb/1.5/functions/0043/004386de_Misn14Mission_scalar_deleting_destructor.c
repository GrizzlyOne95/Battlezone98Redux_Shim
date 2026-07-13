/*
 * Entry: 004386de
 * Name: Misn14Mission::`scalar_deleting_destructor'
 * Namespace: Misn14Mission
 * Signature: void * `scalar_deleting_destructor'(Misn14Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn14Mission::_scalar_deleting_destructor_(Misn14Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
