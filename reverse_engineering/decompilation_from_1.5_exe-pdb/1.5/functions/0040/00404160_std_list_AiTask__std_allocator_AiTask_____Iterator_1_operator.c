/*
 * Entry: 00404160
 * Name: std::list<AiTask_*,std::allocator<AiTask_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<AiTask_*,std::allocator<AiTask_*>_>::_Iterator<1>
 * Signature: AiTask * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiTask ** __thiscall
std::list<AiTask_*,std::allocator<AiTask_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00404033;
    }
  }
  iVar2 = *piVar1;
LAB_00404033:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (AiTask **)(*(int *)&this->field_0x4 + 8);
}
