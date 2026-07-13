/*
 * Entry: 0044be88
 * Name: MPMission::`scalar_deleting_destructor'
 * Namespace: MPMission
 * Signature: void * `scalar_deleting_destructor'(MPMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MPMission::_scalar_deleting_destructor_(MPMission *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
