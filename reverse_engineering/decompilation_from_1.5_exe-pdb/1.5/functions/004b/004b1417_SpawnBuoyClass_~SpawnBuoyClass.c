/*
 * Entry: 004b1417
 * Name: SpawnBuoyClass::~SpawnBuoyClass
 * Namespace: SpawnBuoyClass
 * Signature: void ~SpawnBuoyClass(SpawnBuoyClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpawnBuoyClass::~SpawnBuoyClass(SpawnBuoyClass *this)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
