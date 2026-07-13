/*
 * Entry: 00445d57
 * Name: Misns6Mission::`scalar_deleting_destructor'
 * Namespace: Misns6Mission
 * Signature: void * `scalar_deleting_destructor'(Misns6Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misns6Mission::_scalar_deleting_destructor_(Misns6Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
