/*
 * Entry: 0040bb7b
 * Name: APCProcess::`scalar_deleting_destructor'
 * Namespace: APCProcess
 * Signature: void * `scalar_deleting_destructor'(APCProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall APCProcess::_scalar_deleting_destructor_(APCProcess *this,uint param_1)

{
  ~APCProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
