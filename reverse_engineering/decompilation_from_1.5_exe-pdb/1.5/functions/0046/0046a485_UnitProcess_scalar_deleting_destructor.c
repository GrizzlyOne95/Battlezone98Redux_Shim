/*
 * Entry: 0046a485
 * Name: UnitProcess::`scalar_deleting_destructor'
 * Namespace: UnitProcess
 * Signature: void * `scalar_deleting_destructor'(UnitProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall UnitProcess::_scalar_deleting_destructor_(UnitProcess *this,uint param_1)

{
  ~UnitProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
