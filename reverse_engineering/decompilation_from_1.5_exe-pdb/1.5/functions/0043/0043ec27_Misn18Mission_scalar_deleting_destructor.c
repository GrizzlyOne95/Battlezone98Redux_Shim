/*
 * Entry: 0043ec27
 * Name: Misn18Mission::`scalar_deleting_destructor'
 * Namespace: Misn18Mission
 * Signature: void * `scalar_deleting_destructor'(Misn18Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn18Mission::_scalar_deleting_destructor_(Misn18Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
