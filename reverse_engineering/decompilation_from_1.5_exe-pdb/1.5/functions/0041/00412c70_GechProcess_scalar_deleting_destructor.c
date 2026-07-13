/*
 * Entry: 00412c70
 * Name: GechProcess::`scalar_deleting_destructor'
 * Namespace: GechProcess
 * Signature: void * `scalar_deleting_destructor'(GechProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GechProcess::_scalar_deleting_destructor_(GechProcess *this,uint param_1)

{
  ~GechProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
