/*
 * Entry: 004e6409
 * Name: std::_Move_backward_opt<SpawnPoint_*_*,SpawnPoint_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: SpawnPoint * * _Move_backward_opt<SpawnPoint_*_*,SpawnPoint_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __cdecl
std::
_Move_backward_opt<SpawnPoint_*_*,SpawnPoint_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  SpawnPoint **ppSVar1;
  
  ppSVar1 = _Copy_backward_opt<SpawnPoint_*_*,SpawnPoint_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
