/*
 * Entry: 004e6561
 * Name: std::_Uninit_move<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: SpawnPoint * * _Uninit_move<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>,std::_Undefined_move_tag>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3, allocator<SpawnPoint_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __cdecl
std::
_Uninit_move<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>,std::_Undefined_move_tag>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3,
          allocator<SpawnPoint_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  SpawnPoint **ppSVar1;
  
  ppSVar1 = stdext::
            unchecked_uninitialized_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppSVar1;
}
