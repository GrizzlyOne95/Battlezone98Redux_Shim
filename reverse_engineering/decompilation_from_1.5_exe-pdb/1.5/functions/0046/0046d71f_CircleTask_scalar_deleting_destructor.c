/*
 * Entry: 0046d71f
 * Name: CircleTask::`scalar_deleting_destructor'
 * Namespace: CircleTask
 * Signature: void * `scalar_deleting_destructor'(CircleTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CircleTask::_scalar_deleting_destructor_(CircleTask *this,uint param_1)

{
  ~CircleTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
