/*
 * Entry: 00467713
 * Name: TurretTankProcess::`scalar_deleting_destructor'
 * Namespace: TurretTankProcess
 * Signature: void * `scalar_deleting_destructor'(TurretTankProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
TurretTankProcess::_scalar_deleting_destructor_(TurretTankProcess *this,uint param_1)

{
  ~TurretTankProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
