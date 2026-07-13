/*
 * Entry: 0046d74d
 * Name: CoastTask::`scalar_deleting_destructor'
 * Namespace: CoastTask
 * Signature: void * `scalar_deleting_destructor'(CoastTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CoastTask::_scalar_deleting_destructor_(CoastTask *this,uint param_1)

{
  ~CoastTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
