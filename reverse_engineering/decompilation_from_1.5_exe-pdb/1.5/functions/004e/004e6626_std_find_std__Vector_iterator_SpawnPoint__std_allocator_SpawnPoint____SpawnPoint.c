/*
 * Entry: 004e6626
 * Name: std::find<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>
 * Namespace: std
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> find<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>(_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1, _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> __cdecl
std::find<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>
          (_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1,
          _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_2,SpawnPoint **param_3)

{
  SpawnPoint **ppSVar1;
  SpawnPoint **in_stack_00000018;
  
  ppSVar1 = _Find<SpawnPoint_*_*,SpawnPoint_*>
                      ((SpawnPoint **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(SpawnPoint ***)(param_1._0_4_ + 4) = ppSVar1;
  return param_1;
}
