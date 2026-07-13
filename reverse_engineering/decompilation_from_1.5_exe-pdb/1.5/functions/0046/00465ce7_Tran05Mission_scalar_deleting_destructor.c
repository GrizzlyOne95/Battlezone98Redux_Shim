/*
 * Entry: 00465ce7
 * Name: Tran05Mission::`scalar_deleting_destructor'
 * Namespace: Tran05Mission
 * Signature: void * `scalar_deleting_destructor'(Tran05Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Tran05Mission::_scalar_deleting_destructor_(Tran05Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
