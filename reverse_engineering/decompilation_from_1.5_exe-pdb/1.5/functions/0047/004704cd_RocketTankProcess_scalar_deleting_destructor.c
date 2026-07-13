/*
 * Entry: 004704cd
 * Name: RocketTankProcess::`scalar_deleting_destructor'
 * Namespace: RocketTankProcess
 * Signature: void * `scalar_deleting_destructor'(RocketTankProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
RocketTankProcess::_scalar_deleting_destructor_(RocketTankProcess *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
