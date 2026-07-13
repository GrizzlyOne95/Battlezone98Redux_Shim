/*
 * Entry: 0042f234
 * Name: Misn09Mission::`scalar_deleting_destructor'
 * Namespace: Misn09Mission
 * Signature: void * `scalar_deleting_destructor'(Misn09Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Misn09Mission::_scalar_deleting_destructor_(Misn09Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
