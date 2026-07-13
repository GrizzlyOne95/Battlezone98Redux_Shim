/*
 * Entry: 004489ac
 * Name: Misns7Mission::`scalar_deleting_destructor'
 * Namespace: Misns7Mission
 * Signature: void * `scalar_deleting_destructor'(Misns7Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns7Mission::_scalar_deleting_destructor_(Misns7Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
