/*
 * Entry: 004af38b
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Make_iter
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Make_iter(vector<Scrap_*,std::allocator<Scrap_*>_> * this, _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Make_iter
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this,
          _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Var1;
  Scrap **in_stack_0000000c;
  
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
            ((_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *)param_1._padding_,
             in_stack_0000000c,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
