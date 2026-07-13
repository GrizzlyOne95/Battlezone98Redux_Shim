/*
 * Entry: 00403f0c
 * Name: EmptyMission::`scalar_deleting_destructor'
 * Namespace: EmptyMission
 * Signature: void * `scalar_deleting_destructor'(EmptyMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall EmptyMission::_scalar_deleting_destructor_(EmptyMission *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
