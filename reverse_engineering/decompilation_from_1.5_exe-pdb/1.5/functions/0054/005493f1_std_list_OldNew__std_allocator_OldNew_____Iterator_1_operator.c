/*
 * Entry: 005493f1
 * Name: std::list<OldNew_*,std::allocator<OldNew_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<OldNew_*,std::allocator<OldNew_*>_>::_Iterator<1>
 * Signature: OldNew * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OldNew ** __thiscall
std::list<OldNew_*,std::allocator<OldNew_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00549250;
    }
  }
  iVar2 = *piVar1;
LAB_00549250:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (OldNew **)(*(int *)&this->field_0x4 + 8);
}
