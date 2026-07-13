/*
 * Entry: 00462ed6
 * Name: SoldierProcess::`scalar_deleting_destructor'
 * Namespace: SoldierProcess
 * Signature: void * `scalar_deleting_destructor'(SoldierProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SoldierProcess::_scalar_deleting_destructor_(SoldierProcess *this,uint param_1)

{
  ~SoldierProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
