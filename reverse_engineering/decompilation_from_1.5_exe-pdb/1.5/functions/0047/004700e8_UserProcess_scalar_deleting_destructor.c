/*
 * Entry: 004700e8
 * Name: UserProcess::`scalar_deleting_destructor'
 * Namespace: UserProcess
 * Signature: void * `scalar_deleting_destructor'(UserProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall UserProcess::_scalar_deleting_destructor_(UserProcess *this,uint param_1)

{
  ~UserProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
