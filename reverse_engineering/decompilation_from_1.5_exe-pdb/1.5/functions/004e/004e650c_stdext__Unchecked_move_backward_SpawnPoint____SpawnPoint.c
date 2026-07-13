/*
 * Entry: 004e650c
 * Name: stdext::_Unchecked_move_backward<SpawnPoint_*_*,SpawnPoint_*_*>
 * Namespace: stdext
 * Signature: SpawnPoint * * _Unchecked_move_backward<SpawnPoint_*_*,SpawnPoint_*_*>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __cdecl
stdext::_Unchecked_move_backward<SpawnPoint_*_*,SpawnPoint_*_*>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3)

{
  SpawnPoint **ppSVar1;
  
  ppSVar1 = std::
            _Move_backward_opt<SpawnPoint_*_*,SpawnPoint_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
