/*
 * Entry: 0040d1ce
 * Name: ArmoryProcess::`scalar_deleting_destructor'
 * Namespace: ArmoryProcess
 * Signature: void * `scalar_deleting_destructor'(ArmoryProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ArmoryProcess::_scalar_deleting_destructor_(ArmoryProcess *this,uint param_1)

{
  ~ArmoryProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
