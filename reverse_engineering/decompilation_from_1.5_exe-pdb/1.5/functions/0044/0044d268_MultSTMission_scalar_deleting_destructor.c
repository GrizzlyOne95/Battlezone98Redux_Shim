/*
 * Entry: 0044d268
 * Name: MultSTMission::`scalar_deleting_destructor'
 * Namespace: MultSTMission
 * Signature: void * `scalar_deleting_destructor'(MultSTMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MultSTMission::_scalar_deleting_destructor_(MultSTMission *this,uint param_1)

{
  ~MultSTMission(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
