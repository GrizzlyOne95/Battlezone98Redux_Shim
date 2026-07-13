/*
 * Entry: 0049aaf7
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Make_iter
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Make_iter(vector<Geizer_*,std::allocator<Geizer_*>_> * this, _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Make_iter
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this,
          _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var1;
  Geizer **in_stack_0000000c;
  
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)param_1._padding_,
             in_stack_0000000c,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
