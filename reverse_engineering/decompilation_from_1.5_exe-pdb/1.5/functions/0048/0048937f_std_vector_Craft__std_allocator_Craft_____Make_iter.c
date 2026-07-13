/*
 * Entry: 0048937f
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::_Make_iter
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Make_iter(vector<Craft_*,std::allocator<Craft_*>_> * this, _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::_Make_iter
          (vector<Craft_*,std::allocator<Craft_*>_> *this,
          _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_1)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var1;
  Craft **in_stack_0000000c;
  
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            ((_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *)param_1._padding_,
             in_stack_0000000c,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
