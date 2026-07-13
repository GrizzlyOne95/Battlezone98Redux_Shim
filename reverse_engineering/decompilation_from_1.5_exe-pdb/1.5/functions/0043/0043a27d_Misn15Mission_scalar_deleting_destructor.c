/*
 * Entry: 0043a27d
 * Name: Misn15Mission::`scalar_deleting_destructor'
 * Namespace: Misn15Mission
 * Signature: void * `scalar_deleting_destructor'(Misn15Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn15Mission::_scalar_deleting_destructor_(Misn15Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
