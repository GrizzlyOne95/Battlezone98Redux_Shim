/*
 * Entry: 00452940
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::erase
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> erase(vector<PathPoint,std::allocator<PathPoint>_> * this, _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1, _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::erase
          (vector<PathPoint,std::allocator<PathPoint>_> *this,
          _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1,
          _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_2)

{
  PathPoint *pPVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var2;
  PathPoint *in_stack_00000014;
  
  *(undefined4 *)param_1._padding_ = 0;
  if (((this == (vector<PathPoint,std::allocator<PathPoint>_> *)0x0) ||
      ((uint)param_2._padding_ < this->_Myfirst)) || (this->_Mylast < (uint)param_2._padding_)) {
    _invalid_parameter_noinfo();
    in_EDX = extraout_EDX;
  }
  *(int *)param_1._padding_ = this->_padding_;
  *(int *)(param_1._padding_ + 4) = param_2._padding_;
  if ((in_stack_00000014 < this->_Myfirst) || (this->_Mylast < in_stack_00000014)) {
    _invalid_parameter_noinfo();
    in_EDX = extraout_EDX_00;
  }
  if ((*(int *)param_1._padding_ == 0) || (*(int *)param_1._padding_ != this->_padding_)) {
    _invalid_parameter_noinfo();
    in_EDX = extraout_EDX_01;
  }
  if (*(PathPoint **)(param_1._padding_ + 4) != in_stack_00000014) {
    pPVar1 = _Copy_opt<PathPoint_*,PathPoint_*>
                       (in_stack_00000014,this->_Mylast,*(PathPoint **)(param_1._padding_ + 4),
                        (random_access_iterator_tag)0x0,(_Nonscalar_ptr_iterator_tag)0x0,
                        (_Range_checked_iterator_tag)0x0);
    this->_Mylast = pPVar1;
    in_EDX = extraout_EDX_02;
  }
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1._padding_;
  return _Var2;
}
