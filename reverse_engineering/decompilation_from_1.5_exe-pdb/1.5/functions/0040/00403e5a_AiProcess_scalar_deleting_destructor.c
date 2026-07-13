/*
 * Entry: 00403e5a
 * Name: AiProcess::`scalar_deleting_destructor'
 * Namespace: AiProcess
 * Signature: void * `scalar_deleting_destructor'(AiProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AiProcess::_scalar_deleting_destructor_(AiProcess *this,uint param_1)

{
  ~AiProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
