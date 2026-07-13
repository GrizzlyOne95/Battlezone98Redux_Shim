/*
 * Entry: 00401fde
 * Name: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::operator*
 * Namespace: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>
 * Signature: Craft * * operator*(_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __thiscall
std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::operator*
          (_Vector_iterator<Craft_*,std::allocator<Craft_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00401c04;
    }
  }
  iVar2 = *piVar1;
LAB_00401c04:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(Craft ***)&this->field_0x4;
}
