/*
 * Entry: 004e653c
 * Name: stdext::unchecked_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*>(SpawnPoint * * param_1, uint param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*>
          (SpawnPoint **param_1,uint param_2,SpawnPoint **param_3)

{
  std::_Fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
