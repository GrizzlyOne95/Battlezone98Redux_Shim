/*
 * Entry: 00414aae
 * Name: GotoTask::`scalar_deleting_destructor'
 * Namespace: GotoTask
 * Signature: void * `scalar_deleting_destructor'(GotoTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GotoTask::_scalar_deleting_destructor_(GotoTask *this,uint param_1)

{
  ~GotoTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
