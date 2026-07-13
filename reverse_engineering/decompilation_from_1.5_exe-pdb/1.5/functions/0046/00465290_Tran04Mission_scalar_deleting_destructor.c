/*
 * Entry: 00465290
 * Name: Tran04Mission::`scalar_deleting_destructor'
 * Namespace: Tran04Mission
 * Signature: void * `scalar_deleting_destructor'(Tran04Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Tran04Mission::_scalar_deleting_destructor_(Tran04Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
