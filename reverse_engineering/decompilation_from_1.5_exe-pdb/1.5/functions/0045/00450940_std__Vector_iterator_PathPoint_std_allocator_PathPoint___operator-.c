/*
 * Entry: 00450940
 * Name: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator-=
 * Namespace: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> * operator-=(_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator-=
          (_Vector_iterator<PathPoint,std::allocator<PathPoint>_> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 != (int *)0x0) goto LAB_0045095f;
    iVar2 = 0;
  }
  else {
LAB_0045095f:
    iVar2 = *piVar1;
  }
  uVar3 = *(int *)&this->field_0x4 + param_1 * -0x10;
  if (uVar3 <= *(uint *)(iVar2 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1;
    }
    if (*(uint *)(iVar2 + 0xc) <= uVar3) goto LAB_00450983;
  }
  _invalid_parameter_noinfo();
LAB_00450983:
  *(int *)&this->field_0x4 = *(int *)&this->field_0x4 + param_1 * -0x10;
  return this;
}
