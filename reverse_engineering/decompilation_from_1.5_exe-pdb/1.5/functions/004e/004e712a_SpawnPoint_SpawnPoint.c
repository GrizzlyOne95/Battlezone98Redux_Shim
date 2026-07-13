/*
 * Entry: 004e712a
 * Name: SpawnPoint::SpawnPoint
 * Namespace: SpawnPoint
 * Signature: SpawnPoint * SpawnPoint(SpawnPoint * this, VECTOR_3D param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint * __thiscall SpawnPoint::SpawnPoint(SpawnPoint *this,VECTOR_3D param_1,int param_2)

{
  vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this_00;
  
  this[1].location.x = 0.0;
  (this->location).x = param_1.x;
  (this->location).y = param_1.y;
  (this->location).z = param_1.z;
  this->netPlayer = (NetPlayer *)param_2;
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
  param_2 = (int)this;
  std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::push_back
            (spawnPointList,(SpawnPoint **)&param_2);
  return this;
}
