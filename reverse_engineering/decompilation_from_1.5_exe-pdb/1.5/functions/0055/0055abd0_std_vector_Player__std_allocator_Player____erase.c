/*
 * Entry: 0055abd0
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::erase
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: _Vector_iterator<Player_*,std::allocator<Player_*>_> erase(vector<Player_*,std::allocator<Player_*>_> * this, _Vector_const_iterator<Player_*,std::allocator<Player_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Player_*,std::allocator<Player_*>_> __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::erase
          (vector<Player_*,std::allocator<Player_*>_> *this,
          _Vector_const_iterator<Player_*,std::allocator<Player_*>_> param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Player_*,std::allocator<Player_*>_> _Var1;
  Player **in_stack_0000000c;
  
  stdext::unchecked_copy<Player_*_*,Player_*_*>
            (in_stack_0000000c + 1,this->_Mylast,in_stack_0000000c);
  this->_Mylast = this->_Mylast + -1;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            ((_Vector_const_iterator<Player_*,std::allocator<Player_*>_> *)param_1._padding_,
             in_stack_0000000c,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
