/*
 * Entry: 004514e0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::end
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> end(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::end(vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  Strip **ppSVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Var2;
  int *in_stack_00000004;
  
  ppSVar1 = this->_Mylast;
  *in_stack_00000004 = 0;
  if (ppSVar1 < this->_Myfirst) {
    _invalid_parameter_noinfo();
    in_EDX = extraout_EDX;
  }
  *in_stack_00000004 = this->_padding_;
  in_stack_00000004[1] = (int)ppSVar1;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = in_stack_00000004;
  return _Var2;
}
