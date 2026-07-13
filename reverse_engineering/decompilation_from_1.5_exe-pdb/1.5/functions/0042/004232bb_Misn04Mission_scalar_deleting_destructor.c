/*
 * Entry: 004232bb
 * Name: Misn04Mission::`scalar_deleting_destructor'
 * Namespace: Misn04Mission
 * Signature: void * `scalar_deleting_destructor'(Misn04Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn04Mission::_scalar_deleting_destructor_(Misn04Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
