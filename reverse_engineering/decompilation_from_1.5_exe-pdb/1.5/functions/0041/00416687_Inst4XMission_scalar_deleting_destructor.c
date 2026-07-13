/*
 * Entry: 00416687
 * Name: Inst4XMission::`scalar_deleting_destructor'
 * Namespace: Inst4XMission
 * Signature: void * `scalar_deleting_destructor'(Inst4XMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Inst4XMission::_scalar_deleting_destructor_(Inst4XMission *this,uint param_1)

{
  ~Inst4XMission(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
