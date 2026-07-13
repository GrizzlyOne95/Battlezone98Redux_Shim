/*
 * Entry: 00402269
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Iterator<1>
 * Signature: AiProcess * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiProcess ** __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0040209b;
    }
  }
  iVar2 = *piVar1;
LAB_0040209b:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (AiProcess **)(*(int *)&this->field_0x4 + 8);
}
