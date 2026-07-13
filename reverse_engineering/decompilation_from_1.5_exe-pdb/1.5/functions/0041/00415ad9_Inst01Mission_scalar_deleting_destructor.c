/*
 * Entry: 00415ad9
 * Name: Inst01Mission::`scalar_deleting_destructor'
 * Namespace: Inst01Mission
 * Signature: void * `scalar_deleting_destructor'(Inst01Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Inst01Mission::_scalar_deleting_destructor_(Inst01Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
