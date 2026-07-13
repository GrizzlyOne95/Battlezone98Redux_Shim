/*
 * Entry: 004449df
 * Name: Misns4Mission::`scalar_deleting_destructor'
 * Namespace: Misns4Mission
 * Signature: void * `scalar_deleting_destructor'(Misns4Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns4Mission::_scalar_deleting_destructor_(Misns4Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
