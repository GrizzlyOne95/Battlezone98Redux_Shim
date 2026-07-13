/*
 * Entry: 0044cd8e
 * Name: MultGMission::`scalar_deleting_destructor'
 * Namespace: MultGMission
 * Signature: void * `scalar_deleting_destructor'(MultGMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MultGMission::_scalar_deleting_destructor_(MultGMission *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  AiMission::~AiMission((AiMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
