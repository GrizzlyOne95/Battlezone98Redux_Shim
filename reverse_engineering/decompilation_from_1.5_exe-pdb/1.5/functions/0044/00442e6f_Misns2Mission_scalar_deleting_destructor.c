/*
 * Entry: 00442e6f
 * Name: Misns2Mission::`scalar_deleting_destructor'
 * Namespace: Misns2Mission
 * Signature: void * `scalar_deleting_destructor'(Misns2Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns2Mission::_scalar_deleting_destructor_(Misns2Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
