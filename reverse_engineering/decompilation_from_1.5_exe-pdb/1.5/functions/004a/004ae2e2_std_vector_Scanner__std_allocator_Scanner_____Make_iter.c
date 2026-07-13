/*
 * Entry: 004ae2e2
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Make_iter
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> _Make_iter(vector<Scanner_*,std::allocator<Scanner_*>_> * this, _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Make_iter
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this,
          _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var1;
  Scanner **in_stack_0000000c;
  
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)param_1._padding_,
             in_stack_0000000c,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
