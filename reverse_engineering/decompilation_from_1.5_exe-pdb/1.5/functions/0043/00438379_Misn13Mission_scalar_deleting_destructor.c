/*
 * Entry: 00438379
 * Name: Misn13Mission::`scalar_deleting_destructor'
 * Namespace: Misn13Mission
 * Signature: void * `scalar_deleting_destructor'(Misn13Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn13Mission::_scalar_deleting_destructor_(Misn13Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
