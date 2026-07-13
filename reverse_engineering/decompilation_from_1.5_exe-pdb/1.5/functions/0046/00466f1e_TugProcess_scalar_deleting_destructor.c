/*
 * Entry: 00466f1e
 * Name: TugProcess::`scalar_deleting_destructor'
 * Namespace: TugProcess
 * Signature: void * `scalar_deleting_destructor'(TugProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TugProcess::_scalar_deleting_destructor_(TugProcess *this,uint param_1)

{
  ~TugProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
