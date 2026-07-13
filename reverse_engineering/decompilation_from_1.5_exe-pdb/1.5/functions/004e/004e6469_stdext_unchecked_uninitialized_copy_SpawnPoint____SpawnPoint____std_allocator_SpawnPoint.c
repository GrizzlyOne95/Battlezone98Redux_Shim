/*
 * Entry: 004e6469
 * Name: stdext::unchecked_uninitialized_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>
 * Namespace: stdext
 * Signature: SpawnPoint * * unchecked_uninitialized_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3, allocator<SpawnPoint_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __cdecl
stdext::unchecked_uninitialized_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3,
          allocator<SpawnPoint_*> *param_4)

{
  SpawnPoint **ppSVar1;
  
  ppSVar1 = std::_Uninit_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
