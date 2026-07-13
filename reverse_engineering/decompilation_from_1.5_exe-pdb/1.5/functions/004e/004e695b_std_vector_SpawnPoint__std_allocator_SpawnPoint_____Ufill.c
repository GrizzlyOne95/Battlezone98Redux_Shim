/*
 * Entry: 004e695b
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Ufill
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: SpawnPoint * * _Ufill(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, SpawnPoint * * param_1, uint param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Ufill
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,SpawnPoint **param_1,
          uint param_2,SpawnPoint **param_3)

{
  stdext::unchecked_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
