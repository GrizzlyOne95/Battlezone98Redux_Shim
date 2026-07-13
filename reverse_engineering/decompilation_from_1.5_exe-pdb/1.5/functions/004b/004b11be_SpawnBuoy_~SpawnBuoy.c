/*
 * Entry: 004b11be
 * Name: SpawnBuoy::~SpawnBuoy
 * Namespace: SpawnBuoy
 * Signature: void ~SpawnBuoy(SpawnBuoy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpawnBuoy::~SpawnBuoy(SpawnBuoy *this)

{
  SpawnPoint *this_00;
  
  this_00 = this->spawnPoint;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  if (this_00 != (SpawnPoint *)0x0) {
    SpawnPoint::~SpawnPoint(this_00);
    operator_delete(this_00);
  }
  Building::~Building((Building *)this);
  return;
}
