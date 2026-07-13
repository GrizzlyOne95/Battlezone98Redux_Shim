/*
 * Entry: 004643a3
 * Name: Tran02Mission::`scalar_deleting_destructor'
 * Namespace: Tran02Mission
 * Signature: void * `scalar_deleting_destructor'(Tran02Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Tran02Mission::_scalar_deleting_destructor_(Tran02Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
