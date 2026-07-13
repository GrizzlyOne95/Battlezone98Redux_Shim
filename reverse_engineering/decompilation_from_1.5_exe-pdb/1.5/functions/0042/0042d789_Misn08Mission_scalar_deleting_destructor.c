/*
 * Entry: 0042d789
 * Name: Misn08Mission::`scalar_deleting_destructor'
 * Namespace: Misn08Mission
 * Signature: void * `scalar_deleting_destructor'(Misn08Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn08Mission::_scalar_deleting_destructor_(Misn08Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
