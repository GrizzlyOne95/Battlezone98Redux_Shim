/*
 * Entry: 0045c2f1
 * Name: SAVAttackPersonTask::`scalar_deleting_destructor'
 * Namespace: SAVAttackPersonTask
 * Signature: void * `scalar_deleting_destructor'(SAVAttackPersonTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SAVAttackPersonTask::_scalar_deleting_destructor_(SAVAttackPersonTask *this,uint param_1)

{
  ~SAVAttackPersonTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
