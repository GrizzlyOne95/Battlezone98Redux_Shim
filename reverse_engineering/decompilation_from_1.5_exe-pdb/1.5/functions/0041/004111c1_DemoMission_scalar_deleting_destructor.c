/*
 * Entry: 004111c1
 * Name: DemoMission::`scalar_deleting_destructor'
 * Namespace: DemoMission
 * Signature: void * `scalar_deleting_destructor'(DemoMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall DemoMission::_scalar_deleting_destructor_(DemoMission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
