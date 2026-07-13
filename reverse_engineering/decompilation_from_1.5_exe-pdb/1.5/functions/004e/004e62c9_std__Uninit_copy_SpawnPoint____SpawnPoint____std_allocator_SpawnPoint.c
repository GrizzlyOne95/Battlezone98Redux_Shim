/*
 * Entry: 004e62c9
 * Name: std::_Uninit_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>
 * Namespace: std
 * Signature: SpawnPoint * * _Uninit_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3, allocator<SpawnPoint_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __cdecl
std::_Uninit_copy<SpawnPoint_*_*,SpawnPoint_*_*,std::allocator<SpawnPoint_*>_>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3,
          allocator<SpawnPoint_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
