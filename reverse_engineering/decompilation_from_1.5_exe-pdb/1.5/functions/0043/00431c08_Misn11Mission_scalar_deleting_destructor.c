/*
 * Entry: 00431c08
 * Name: Misn11Mission::`scalar_deleting_destructor'
 * Namespace: Misn11Mission
 * Signature: void * `scalar_deleting_destructor'(Misn11Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn11Mission::_scalar_deleting_destructor_(Misn11Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
