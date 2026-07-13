/*
 * Entry: 0042645a
 * Name: Misn05Mission::`scalar_deleting_destructor'
 * Namespace: Misn05Mission
 * Signature: void * `scalar_deleting_destructor'(Misn05Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn05Mission::_scalar_deleting_destructor_(Misn05Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
