/*
 * Entry: 0047035b
 * Name: ScoutProcess::`scalar_deleting_destructor'
 * Namespace: ScoutProcess
 * Signature: void * `scalar_deleting_destructor'(ScoutProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScoutProcess::_scalar_deleting_destructor_(ScoutProcess *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
