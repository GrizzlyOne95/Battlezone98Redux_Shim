/*
 * Entry: 0046dab2
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>
 * Signature: Ordnance * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance ** __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0046d698;
    }
  }
  iVar2 = *piVar1;
LAB_0046d698:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (Ordnance **)(*(int *)&this->field_0x4 + 8);
}
