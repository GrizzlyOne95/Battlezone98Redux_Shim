/*
 * Entry: 00409193
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::begin
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> begin(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::begin
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var1;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
