/*
 * Entry: 004e70c8
 * Name: SpawnPoint::SpawnPoint
 * Namespace: SpawnPoint
 * Signature: SpawnPoint * SpawnPoint(SpawnPoint * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint * __thiscall SpawnPoint::SpawnPoint(SpawnPoint *this)

{
  vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this_00;
  SpawnPoint *local_8;
  
  this->netPlayer = (NetPlayer *)0x0;
  this[1].location.x = 0.0;
  (this->location).x = 0.0;
  (this->location).y = 0.0;
  (this->location).z = 0.0;
  if (spawnPointList == (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) {
    this_00 = operator_new(0x18);
    if (this_00 == (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) {
      spawnPointList = (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0;
    }
    else {
      spawnPointList =
           std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
           vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>(this_00);
    }
  }
  local_8 = this;
  std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::push_back(spawnPointList,&local_8);
  return this;
}
