/*
 * Entry: 00450f30
 * Name: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator-
 * Namespace: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> operator-(_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> __thiscall
std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator-
          (_Vector_iterator<PathPoint,std::allocator<PathPoint>_> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  uint uVar4;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var5;
  int in_stack_00000008;
  
  iVar3 = *(int *)&this->field_0x4;
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar2 = 0;
    in_EDX = extraout_EDX;
  }
  else {
    iVar2 = *piVar1;
  }
  uVar4 = in_stack_00000008 * -0x10 + iVar3;
  if (uVar4 <= *(uint *)(iVar2 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *piVar1;
    }
    if (*(uint *)(iVar3 + 0xc) <= uVar4) goto LAB_00450f6c;
  }
  _invalid_parameter_noinfo();
  in_EDX = extraout_EDX_00;
LAB_00450f6c:
  *(int **)param_1 = piVar1;
  *(uint *)(param_1 + 4) = uVar4;
  _Var5._4_4_ = in_EDX;
  _Var5._0_4_ = param_1;
  return _Var5;
}
