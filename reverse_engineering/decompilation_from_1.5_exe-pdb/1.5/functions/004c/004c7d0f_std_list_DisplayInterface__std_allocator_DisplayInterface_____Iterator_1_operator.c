/*
 * Entry: 004c7d0f
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Iterator<1>
 * Signature: DisplayInterface * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DisplayInterface ** __thiscall
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Iterator<1>::operator*
          (_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004c7b0f;
    }
  }
  iVar2 = *piVar1;
LAB_004c7b0f:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (DisplayInterface **)(*(int *)&this->field_0x4 + 8);
}
