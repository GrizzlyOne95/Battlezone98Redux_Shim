/*
 * Entry: 0046d769
 * Name: UnitTask::`scalar_deleting_destructor'
 * Namespace: UnitTask
 * Signature: void * `scalar_deleting_destructor'(UnitTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall UnitTask::_scalar_deleting_destructor_(UnitTask *this,uint param_1)

{
  ~UnitTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
