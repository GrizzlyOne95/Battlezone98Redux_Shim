/*
 * Entry: 00414fb9
 * Name: GunTowerAttack::~GunTowerAttack
 * Namespace: GunTowerAttack
 * Signature: void ~GunTowerAttack(GunTowerAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GunTowerAttack::~GunTowerAttack(GunTowerAttack *this)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
