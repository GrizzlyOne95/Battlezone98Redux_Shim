/*
 * Entry: 004e671b
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> unchecked_remove_copy<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>(_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1, _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_2, _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_3, SpawnPoint * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>
          (_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1,
          _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_2,
          _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_3,SpawnPoint **param_4)

{
  _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<SpawnPoint_*_*,std::_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>,SpawnPoint_*>
                    ((SpawnPoint **)param_1._0_4_,(SpawnPoint **)param_2._0_4_,param_3,param_4,
                     in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
