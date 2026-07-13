/*
 * Entry: 00410798
 * Name: RigProcess::`scalar_deleting_destructor'
 * Namespace: RigProcess
 * Signature: void * `scalar_deleting_destructor'(RigProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RigProcess::_scalar_deleting_destructor_(RigProcess *this,uint param_1)

{
  ~RigProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
