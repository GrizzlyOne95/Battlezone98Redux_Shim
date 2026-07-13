/*
 * Entry: 0045b232
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::end
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> end(vector<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::end(vector<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Var1;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
