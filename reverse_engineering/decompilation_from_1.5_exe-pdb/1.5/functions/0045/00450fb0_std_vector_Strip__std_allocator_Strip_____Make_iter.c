/*
 * Entry: 00450fb0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Make_iter
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Make_iter(vector<Strip_*,std::allocator<Strip_*>_> * this, _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::_Make_iter
          (vector<Strip_*,std::allocator<Strip_*>_> *this,
          _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1)

{
  int iVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Var2;
  Strip **in_stack_0000000c;
  
  *(undefined4 *)param_1._padding_ = 0;
  if (((this == (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) ||
      (in_stack_0000000c < this->_Myfirst)) || (this->_Mylast < in_stack_0000000c)) {
    _invalid_parameter_noinfo();
    in_EDX = extraout_EDX;
  }
  iVar1 = this->_padding_;
  *(Strip ***)(param_1._padding_ + 4) = in_stack_0000000c;
  *(int *)param_1._padding_ = iVar1;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1._padding_;
  return _Var2;
}
