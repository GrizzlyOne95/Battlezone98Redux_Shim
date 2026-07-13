/*
 * Entry: 00451070
 * Name: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator-=
 * Namespace: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> * operator-=(_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * __thiscall
std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator-=
          (_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 != (int *)0x0) goto LAB_0045108f;
    iVar2 = 0;
  }
  else {
LAB_0045108f:
    iVar2 = *piVar1;
  }
  uVar3 = *(int *)&this->field_0x4 + param_1 * -4;
  if (uVar3 <= *(uint *)(iVar2 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1;
    }
    if (*(uint *)(iVar2 + 0xc) <= uVar3) goto LAB_004510b4;
  }
  _invalid_parameter_noinfo();
LAB_004510b4:
  *(int *)&this->field_0x4 = *(int *)&this->field_0x4 + param_1 * -4;
  return this;
}
