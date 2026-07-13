/*
 * Entry: 004c7d0a
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>
 * Signature: DisplayViewInfo * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DisplayViewInfo ** __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::operator*
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
      goto LAB_004c7aac;
    }
  }
  iVar2 = *piVar1;
LAB_004c7aac:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (DisplayViewInfo **)(*(int *)&this->field_0x4 + 8);
}
