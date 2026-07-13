/*
 * Entry: 00467948
 * Name: TurretTankEnemy::`scalar_deleting_destructor'
 * Namespace: TurretTankEnemy
 * Signature: void * `scalar_deleting_destructor'(TurretTankEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TurretTankEnemy::_scalar_deleting_destructor_(TurretTankEnemy *this,uint param_1)

{
  TurretTankProcess::~TurretTankProcess((TurretTankProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
