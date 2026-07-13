/*
 * Entry: 005582c2
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::end
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: _Vector_iterator<Player_*,std::allocator<Player_*>_> end(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Player_*,std::allocator<Player_*>_> __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::end
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Player_*,std::allocator<Player_*>_> _Var1;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
