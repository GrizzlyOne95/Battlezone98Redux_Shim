/*
 * Entry: 005493d7
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>::_Iterator<1>
 * Signature: Addr * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Addr ** __thiscall
std::list<Addr_*,std::allocator<Addr_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_005491ee;
    }
  }
  iVar2 = *piVar1;
LAB_005491ee:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (Addr **)(*(int *)&this->field_0x4 + 8);
}
