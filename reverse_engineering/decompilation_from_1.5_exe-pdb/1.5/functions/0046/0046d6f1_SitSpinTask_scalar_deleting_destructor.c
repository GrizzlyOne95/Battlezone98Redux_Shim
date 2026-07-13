/*
 * Entry: 0046d6f1
 * Name: SitSpinTask::`scalar_deleting_destructor'
 * Namespace: SitSpinTask
 * Signature: void * `scalar_deleting_destructor'(SitSpinTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SitSpinTask::_scalar_deleting_destructor_(SitSpinTask *this,uint param_1)

{
  ~SitSpinTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
