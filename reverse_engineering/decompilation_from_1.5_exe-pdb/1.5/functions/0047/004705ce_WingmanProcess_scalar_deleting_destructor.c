/*
 * Entry: 004705ce
 * Name: WingmanProcess::`scalar_deleting_destructor'
 * Namespace: WingmanProcess
 * Signature: void * `scalar_deleting_destructor'(WingmanProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall WingmanProcess::_scalar_deleting_destructor_(WingmanProcess *this,uint param_1)

{
  ~WingmanProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
