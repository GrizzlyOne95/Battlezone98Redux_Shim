/*
 * Entry: 00467508
 * Name: TurretTankEnemy::~TurretTankEnemy
 * Namespace: TurretTankEnemy
 * Signature: void ~TurretTankEnemy(TurretTankEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankEnemy::~TurretTankEnemy(TurretTankEnemy *this)

{
  *(undefined ***)this = &TurretTankProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
