/*
 * Entry: 0044dcee
 * Name: OffensiveProcess::`scalar_deleting_destructor'
 * Namespace: OffensiveProcess
 * Signature: void * `scalar_deleting_destructor'(OffensiveProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
OffensiveProcess::_scalar_deleting_destructor_(OffensiveProcess *this,uint param_1)

{
  ~OffensiveProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
