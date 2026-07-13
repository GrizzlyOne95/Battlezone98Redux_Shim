/*
 * Entry: 0040310d
 * Name: AiMission::`scalar_deleting_destructor'
 * Namespace: AiMission
 * Signature: void * `scalar_deleting_destructor'(AiMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AiMission::_scalar_deleting_destructor_(AiMission *this,uint param_1)

{
  ~AiMission(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
