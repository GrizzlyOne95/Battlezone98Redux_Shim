/*
 * Entry: 00403561
 * Name: std::list<AiPath_*,std::allocator<AiPath_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<AiPath_*,std::allocator<AiPath_*>_>::_Iterator<1>
 * Signature: AiPath * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath ** __thiscall
std::list<AiPath_*,std::allocator<AiPath_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004034ca;
    }
  }
  iVar2 = *piVar1;
LAB_004034ca:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (AiPath **)(*(int *)&this->field_0x4 + 8);
}
