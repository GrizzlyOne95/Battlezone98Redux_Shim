/*
 * Entry: 0053eb60
 * Name: std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::operator*
 * Namespace: std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: WeaponClass * * operator*(_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __thiscall
std::_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_>::operator*
          (_Vector_iterator<WeaponClass_*,std::allocator<WeaponClass_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0053e8dd;
    }
  }
  iVar2 = *piVar1;
LAB_0053e8dd:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(WeaponClass ***)&this->field_0x4;
}
