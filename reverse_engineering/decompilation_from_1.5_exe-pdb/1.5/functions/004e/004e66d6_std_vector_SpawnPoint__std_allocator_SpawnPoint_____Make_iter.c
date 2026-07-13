/*
 * Entry: 004e66d6
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Make_iter
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Make_iter(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Make_iter
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,
          _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var1;
  SpawnPoint **in_stack_0000000c;
  
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)param_1._padding_
             ,in_stack_0000000c,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
