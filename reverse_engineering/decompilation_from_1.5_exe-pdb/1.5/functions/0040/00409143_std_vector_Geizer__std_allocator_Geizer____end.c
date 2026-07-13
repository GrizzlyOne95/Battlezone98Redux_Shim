/*
 * Entry: 00409143
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::end
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> end(vector<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::end
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var1;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *in_stack_00000004;
  
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (in_stack_00000004,this->_Mylast,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
