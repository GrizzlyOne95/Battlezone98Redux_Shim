/*
 * Entry: 00414c8a
 * Name: GunTowerProcess::~GunTowerProcess
 * Namespace: GunTowerProcess
 * Signature: void ~GunTowerProcess(GunTowerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GunTowerProcess::~GunTowerProcess(GunTowerProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
