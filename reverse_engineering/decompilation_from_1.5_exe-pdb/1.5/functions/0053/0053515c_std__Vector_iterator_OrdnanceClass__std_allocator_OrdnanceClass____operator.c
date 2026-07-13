/*
 * Entry: 0053515c
 * Name: std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::operator*
 * Namespace: std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: OrdnanceClass * * operator*(_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __thiscall
std::_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::operator*
          (_Vector_iterator<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00534ef4;
    }
  }
  iVar2 = *piVar1;
LAB_00534ef4:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(OrdnanceClass ***)&this->field_0x4;
}
