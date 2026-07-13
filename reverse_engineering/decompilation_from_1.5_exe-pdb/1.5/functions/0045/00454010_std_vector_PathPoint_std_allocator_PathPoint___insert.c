/*
 * Entry: 00454010
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::insert
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> insert(vector<PathPoint,std::allocator<PathPoint>_> * this, _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1, PathPoint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::insert
          (vector<PathPoint,std::allocator<PathPoint>_> *this,
          _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> param_1,PathPoint *param_2)

{
  int *piVar1;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var2;
  int iVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar4;
  int iVar5;
  PathPoint *pPVar6;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var7;
  PathPoint *in_stack_00000010;
  
  pPVar6 = this->_Myfirst;
  if (((int)this->_Mylast - (int)pPVar6 & 0xfffffff0U) == 0) {
    iVar5 = 0;
  }
  else {
    if (this->_Mylast < pPVar6) {
      _invalid_parameter_noinfo();
    }
    if ((param_1._Myptr == (PathPoint *)0x0) || (param_1._Myptr != (PathPoint *)this->_padding_)) {
      _invalid_parameter_noinfo();
    }
    iVar5 = (int)param_2 - (int)pPVar6 >> 4;
  }
  _Var2._Myptr = param_2;
  _Var2._padding_ = (int)param_1._Myptr;
  _Insert_n(this,_Var2,1,in_stack_00000010);
  pPVar6 = this->_Myfirst;
  uVar4 = extraout_EDX;
  if (this->_Mylast < pPVar6) {
    _invalid_parameter_noinfo();
    uVar4 = extraout_EDX_00;
  }
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
    uVar4 = extraout_EDX_01;
  }
  else {
    iVar3 = *piVar1;
  }
  pPVar6 = pPVar6 + iVar5;
  if (pPVar6 <= *(PathPoint **)(iVar3 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *piVar1;
    }
    if (*(PathPoint **)(iVar5 + 0xc) <= pPVar6) goto LAB_004540b3;
  }
  _invalid_parameter_noinfo();
  uVar4 = extraout_EDX_02;
LAB_004540b3:
  *(PathPoint **)(param_1._padding_ + 4) = pPVar6;
  *(int **)param_1._padding_ = piVar1;
  _Var7._4_4_ = uVar4;
  _Var7._0_4_ = param_1._padding_;
  return _Var7;
}
