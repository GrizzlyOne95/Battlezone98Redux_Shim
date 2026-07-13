/*
 * Entry: 004318e4
 * Name: Misn10Mission::`scalar_deleting_destructor'
 * Namespace: Misn10Mission
 * Signature: void * `scalar_deleting_destructor'(Misn10Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn10Mission::_scalar_deleting_destructor_(Misn10Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
