/*
 * Entry: 0046d6c3
 * Name: SitTask::`scalar_deleting_destructor'
 * Namespace: SitTask
 * Signature: void * `scalar_deleting_destructor'(SitTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SitTask::_scalar_deleting_destructor_(SitTask *this,uint param_1)

{
  ~SitTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
