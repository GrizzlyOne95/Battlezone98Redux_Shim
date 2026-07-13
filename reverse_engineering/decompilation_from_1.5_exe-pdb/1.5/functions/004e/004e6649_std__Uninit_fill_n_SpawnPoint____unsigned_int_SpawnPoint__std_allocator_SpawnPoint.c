/*
 * Entry: 004e6649
 * Name: std::_Uninit_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*,std::allocator<SpawnPoint_*>_>(SpawnPoint * * param_1, uint param_2, SpawnPoint * * param_3, allocator<SpawnPoint_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*,std::allocator<SpawnPoint_*>_>
          (SpawnPoint **param_1,uint param_2,SpawnPoint **param_3,allocator<SpawnPoint_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<SpawnPoint_*_*,unsigned_int,SpawnPoint_*>(param_1,param_2,param_3);
  return;
}
