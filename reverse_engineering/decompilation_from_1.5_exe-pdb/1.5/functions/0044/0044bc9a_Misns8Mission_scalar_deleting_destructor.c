/*
 * Entry: 0044bc9a
 * Name: Misns8Mission::`scalar_deleting_destructor'
 * Namespace: Misns8Mission
 * Signature: void * `scalar_deleting_destructor'(Misns8Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns8Mission::_scalar_deleting_destructor_(Misns8Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
