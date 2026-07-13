/*
 * Entry: 00497660
 * Name: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator*
 * Namespace: std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: Scanner * * operator*(_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __thiscall
std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator*
          (_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004969f3;
    }
  }
  iVar2 = *piVar1;
LAB_004969f3:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(Scanner ***)&this->field_0x4;
}
