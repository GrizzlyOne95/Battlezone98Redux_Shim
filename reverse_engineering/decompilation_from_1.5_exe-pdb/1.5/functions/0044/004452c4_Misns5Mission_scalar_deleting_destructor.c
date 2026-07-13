/*
 * Entry: 004452c4
 * Name: Misns5Mission::`scalar_deleting_destructor'
 * Namespace: Misns5Mission
 * Signature: void * `scalar_deleting_destructor'(Misns5Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns5Mission::_scalar_deleting_destructor_(Misns5Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
