/*
 * Entry: 0045b938
 * Name: RescueTask::`scalar_deleting_destructor'
 * Namespace: RescueTask
 * Signature: void * `scalar_deleting_destructor'(RescueTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RescueTask::_scalar_deleting_destructor_(RescueTask *this,uint param_1)

{
  ~RescueTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
