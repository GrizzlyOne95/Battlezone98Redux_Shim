/*
 * Entry: 0041d83d
 * Name: Misn01Mission::`scalar_deleting_destructor'
 * Namespace: Misn01Mission
 * Signature: void * `scalar_deleting_destructor'(Misn01Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn01Mission::_scalar_deleting_destructor_(Misn01Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
