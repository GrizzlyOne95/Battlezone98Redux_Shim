/*
 * Entry: 00414c73
 * Name: GunTowerProcess::GunTowerProcess
 * Namespace: GunTowerProcess
 * Signature: GunTowerProcess * GunTowerProcess(GunTowerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GunTowerProcess * __thiscall GunTowerProcess::GunTowerProcess(GunTowerProcess *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  *(undefined4 *)&this->field_0x28 = 0;
  *(undefined ***)this = &_vftable_;
  return this;
}
