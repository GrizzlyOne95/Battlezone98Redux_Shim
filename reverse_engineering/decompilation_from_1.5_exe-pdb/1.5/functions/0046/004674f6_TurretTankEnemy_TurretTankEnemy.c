/*
 * Entry: 004674f6
 * Name: TurretTankEnemy::TurretTankEnemy
 * Namespace: TurretTankEnemy
 * Signature: TurretTankEnemy * TurretTankEnemy(TurretTankEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretTankEnemy * __thiscall TurretTankEnemy::TurretTankEnemy(TurretTankEnemy *this)

{
  TurretTankProcess::TurretTankProcess((TurretTankProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
