/*
 * Entry: 00440421
 * Name: Misns1Mission::`scalar_deleting_destructor'
 * Namespace: Misns1Mission
 * Signature: void * `scalar_deleting_destructor'(Misns1Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns1Mission::_scalar_deleting_destructor_(Misns1Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
