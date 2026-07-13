/*
 * Entry: 00457632
 * Name: PersonProcess::`scalar_deleting_destructor'
 * Namespace: PersonProcess
 * Signature: void * `scalar_deleting_destructor'(PersonProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonProcess::_scalar_deleting_destructor_(PersonProcess *this,uint param_1)

{
  ~PersonProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
