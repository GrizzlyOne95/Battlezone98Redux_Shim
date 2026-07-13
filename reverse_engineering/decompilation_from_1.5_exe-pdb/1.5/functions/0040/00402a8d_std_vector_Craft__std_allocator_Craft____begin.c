/*
 * Entry: 00402a8d
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::begin
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> begin(vector<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::begin(vector<Craft_*,std::allocator<Craft_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var1;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
