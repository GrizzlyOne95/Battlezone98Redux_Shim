/*
 * Entry: 00410e41
 * Name: DefendTask::`scalar_deleting_destructor'
 * Namespace: DefendTask
 * Signature: void * `scalar_deleting_destructor'(DefendTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall DefendTask::_scalar_deleting_destructor_(DefendTask *this,uint param_1)

{
  ~DefendTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
