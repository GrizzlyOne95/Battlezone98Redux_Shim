/*
 * Entry: 0045991a
 * Name: RecyclerProcess::`scalar_deleting_destructor'
 * Namespace: RecyclerProcess
 * Signature: void * `scalar_deleting_destructor'(RecyclerProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RecyclerProcess::_scalar_deleting_destructor_(RecyclerProcess *this,uint param_1)

{
  ~RecyclerProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
