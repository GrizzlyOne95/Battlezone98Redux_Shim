/*
 * Entry: 0045b9b6
 * Name: SAVProcess::`scalar_deleting_destructor'
 * Namespace: SAVProcess
 * Signature: void * `scalar_deleting_destructor'(SAVProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SAVProcess::_scalar_deleting_destructor_(SAVProcess *this,uint param_1)

{
  ~SAVProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
