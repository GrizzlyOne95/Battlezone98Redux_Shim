/*
 * Entry: 00451020
 * Name: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator+
 * Namespace: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> operator+(_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> __thiscall
std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator+
          (_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *this,int param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Var5;
  int in_stack_00000008;
  
  piVar2 = *(int **)this;
  iVar4 = *(int *)&this->field_0x4;
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
    in_EDX = extraout_EDX;
  }
  else {
    iVar3 = *piVar2;
  }
  uVar1 = iVar4 + in_stack_00000008 * 4;
  if (uVar1 <= *(uint *)(iVar3 + 0x10)) {
    if (piVar2 == (int *)0x0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *piVar2;
    }
    if (*(uint *)(iVar4 + 0xc) <= uVar1) goto LAB_00451057;
  }
  _invalid_parameter_noinfo();
  in_EDX = extraout_EDX_00;
LAB_00451057:
  *(uint *)(param_1 + 4) = uVar1;
  *(int **)param_1 = piVar2;
  _Var5._4_4_ = in_EDX;
  _Var5._0_4_ = param_1;
  return _Var5;
}
