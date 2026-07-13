/*
 * Entry: 0040b346
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>
 * Signature: AOI * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AOI ** __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0040b26d;
    }
  }
  iVar2 = *piVar1;
LAB_0040b26d:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (AOI **)(*(int *)&this->field_0x4 + 8);
}
