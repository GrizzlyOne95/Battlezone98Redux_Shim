/*
 * Entry: 004521b0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::_Make_iter
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Make_iter(vector<PathPoint,std::allocator<PathPoint>_> * this, _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::_Make_iter
          (vector<PathPoint,std::allocator<PathPoint>_> *this,
          _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1)

{
  int iVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var2;
  PathPoint *in_stack_0000000c;
  
  *(undefined4 *)param_1._padding_ = 0;
  if (((this == (vector<PathPoint,std::allocator<PathPoint>_> *)0x0) ||
      (in_stack_0000000c < this->_Myfirst)) || (this->_Mylast < in_stack_0000000c)) {
    _invalid_parameter_noinfo();
    in_EDX = extraout_EDX;
  }
  iVar1 = this->_padding_;
  *(PathPoint **)(param_1._padding_ + 4) = in_stack_0000000c;
  *(int *)param_1._padding_ = iVar1;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1._padding_;
  return _Var2;
}
