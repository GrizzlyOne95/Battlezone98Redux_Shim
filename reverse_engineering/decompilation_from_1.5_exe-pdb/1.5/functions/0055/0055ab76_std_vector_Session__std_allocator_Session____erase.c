/*
 * Entry: 0055ab76
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::erase
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: _Vector_iterator<Session_*,std::allocator<Session_*>_> erase(vector<Session_*,std::allocator<Session_*>_> * this, _Vector_const_iterator<Session_*,std::allocator<Session_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Session_*,std::allocator<Session_*>_> __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::erase
          (vector<Session_*,std::allocator<Session_*>_> *this,
          _Vector_const_iterator<Session_*,std::allocator<Session_*>_> param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Session_*,std::allocator<Session_*>_> _Var1;
  Session **in_stack_0000000c;
  
  stdext::unchecked_copy<Session_*_*,Session_*_*>
            (in_stack_0000000c + 1,this->_Mylast,in_stack_0000000c);
  this->_Mylast = this->_Mylast + -1;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            ((_Vector_const_iterator<Session_*,std::allocator<Session_*>_> *)param_1._padding_,
             in_stack_0000000c,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
