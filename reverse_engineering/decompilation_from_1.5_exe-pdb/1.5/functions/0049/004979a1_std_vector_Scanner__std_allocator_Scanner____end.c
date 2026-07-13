/*
 * Entry: 004979a1
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::end
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> end(vector<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::end
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var1;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
