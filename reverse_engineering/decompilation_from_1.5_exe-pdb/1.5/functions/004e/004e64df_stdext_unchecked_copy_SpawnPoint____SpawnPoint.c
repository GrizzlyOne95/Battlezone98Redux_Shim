/*
 * Entry: 004e64df
 * Name: stdext::unchecked_copy<SpawnPoint_*_*,SpawnPoint_*_*>
 * Namespace: stdext
 * Signature: SpawnPoint * * unchecked_copy<SpawnPoint_*_*,SpawnPoint_*_*>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __cdecl
stdext::unchecked_copy<SpawnPoint_*_*,SpawnPoint_*_*>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3)

{
  SpawnPoint **ppSVar1;
  
  ppSVar1 = std::_Copy_opt<SpawnPoint_*_*,SpawnPoint_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
