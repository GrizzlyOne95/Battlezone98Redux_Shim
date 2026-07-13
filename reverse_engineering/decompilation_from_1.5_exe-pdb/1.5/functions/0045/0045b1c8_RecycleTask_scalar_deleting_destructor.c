/*
 * Entry: 0045b1c8
 * Name: RecycleTask::`scalar_deleting_destructor'
 * Namespace: RecycleTask
 * Signature: void * `scalar_deleting_destructor'(RecycleTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RecycleTask::_scalar_deleting_destructor_(RecycleTask *this,uint param_1)

{
  ~RecycleTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
