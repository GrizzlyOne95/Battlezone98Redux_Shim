/*
 * Entry: 004441b5
 * Name: Misns3Mission::`scalar_deleting_destructor'
 * Namespace: Misns3Mission
 * Signature: void * `scalar_deleting_destructor'(Misns3Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns3Mission::_scalar_deleting_destructor_(Misns3Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
