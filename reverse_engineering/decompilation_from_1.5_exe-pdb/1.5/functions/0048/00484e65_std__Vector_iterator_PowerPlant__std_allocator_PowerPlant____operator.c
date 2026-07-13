/*
 * Entry: 00484e65
 * Name: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator*
 * Namespace: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: PowerPlant * * operator*(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __thiscall
std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator*
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00484dda;
    }
  }
  iVar2 = *piVar1;
LAB_00484dda:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(PowerPlant ***)&this->field_0x4;
}
