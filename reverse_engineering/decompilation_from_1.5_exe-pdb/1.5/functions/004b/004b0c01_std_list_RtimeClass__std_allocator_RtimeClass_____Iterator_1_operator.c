/*
 * Entry: 004b0c01
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Iterator<1>
 * Signature: RtimeClass * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RtimeClass ** __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004b0b23;
    }
  }
  iVar2 = *piVar1;
LAB_004b0b23:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (RtimeClass **)(*(int *)&this->field_0x4 + 8);
}
