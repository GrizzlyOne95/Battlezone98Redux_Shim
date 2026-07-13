/*
 * Entry: 0040ee7c
 * Name: AttackTask::`scalar_deleting_destructor'
 * Namespace: AttackTask
 * Signature: void * `scalar_deleting_destructor'(AttackTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AttackTask::_scalar_deleting_destructor_(AttackTask *this,uint param_1)

{
  ~AttackTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
