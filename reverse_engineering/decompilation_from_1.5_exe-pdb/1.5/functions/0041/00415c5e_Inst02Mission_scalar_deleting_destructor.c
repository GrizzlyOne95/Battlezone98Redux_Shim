/*
 * Entry: 00415c5e
 * Name: Inst02Mission::`scalar_deleting_destructor'
 * Namespace: Inst02Mission
 * Signature: void * `scalar_deleting_destructor'(Inst02Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Inst02Mission::_scalar_deleting_destructor_(Inst02Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
