/*
 * Entry: 004d01ca
 * Name: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Iterator<1>
 * Signature: AdjustItem * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AdjustItem ** __thiscall
std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004d0111;
    }
  }
  iVar2 = *piVar1;
LAB_004d0111:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (AdjustItem **)(*(int *)&this->field_0x4 + 8);
}
