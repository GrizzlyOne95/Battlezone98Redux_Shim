/*
 * Entry: 00414d14
 * Name: GunTowerEnemy::~GunTowerEnemy
 * Namespace: GunTowerEnemy
 * Signature: void ~GunTowerEnemy(GunTowerEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GunTowerEnemy::~GunTowerEnemy(GunTowerEnemy *this)

{
  *(undefined ***)this = &GunTowerProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
