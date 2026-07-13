/*
 * Entry: 00464a91
 * Name: Tran03Mission::`scalar_deleting_destructor'
 * Namespace: Tran03Mission
 * Signature: void * `scalar_deleting_destructor'(Tran03Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Tran03Mission::_scalar_deleting_destructor_(Tran03Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
