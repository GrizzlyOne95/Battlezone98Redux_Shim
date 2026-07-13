/*
 * Entry: 004b1162
 * Name: SpawnBuoy::Cleanup
 * Namespace: SpawnBuoy
 * Signature: void Cleanup(SpawnBuoy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpawnBuoy::Cleanup(SpawnBuoy *this)

{
  SpawnPoint *this_00;
  bool bVar1;
  
  bVar1 = Net::IsNetGame();
  if (bVar1) {
    this_00 = this->spawnPoint;
    if (this_00 != (SpawnPoint *)0x0) {
      SpawnPoint::~SpawnPoint(this_00);
      operator_delete(this_00);
    }
    this->spawnPoint = (SpawnPoint *)0x0;
  }
  Building::Cleanup((Building *)this);
  return;
}
