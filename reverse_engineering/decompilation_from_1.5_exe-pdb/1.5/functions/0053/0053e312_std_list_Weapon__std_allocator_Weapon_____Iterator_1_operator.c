/*
 * Entry: 0053e312
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>
 * Signature: Weapon * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon ** __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0053e22c;
    }
  }
  iVar2 = *piVar1;
LAB_0053e22c:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (Weapon **)(*(int *)&this->field_0x4 + 8);
}
