/*
 * Entry: 004b1472
 * Name: SpawnBuoyClass::SpawnBuoyClass
 * Namespace: SpawnBuoyClass
 * Signature: SpawnBuoyClass * SpawnBuoyClass(SpawnBuoyClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnBuoyClass * __thiscall SpawnBuoyClass::SpawnBuoyClass(SpawnBuoyClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x5350574e;
  *(char **)&this->field_0x24 = "spawnpnt";
  *(undefined4 *)&this->field_0x28 = 5;
  return this;
}
