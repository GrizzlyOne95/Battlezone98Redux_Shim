/*
 * Entry: 0042bae7
 * Name: Misn07Mission::`scalar_deleting_destructor'
 * Namespace: Misn07Mission
 * Signature: void * `scalar_deleting_destructor'(Misn07Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn07Mission::_scalar_deleting_destructor_(Misn07Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
