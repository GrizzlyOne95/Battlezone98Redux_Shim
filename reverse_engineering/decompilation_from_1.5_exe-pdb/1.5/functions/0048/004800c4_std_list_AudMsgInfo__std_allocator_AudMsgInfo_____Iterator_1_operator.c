/*
 * Entry: 004800c4
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Iterator<1>
 * Signature: AudMsgInfo * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AudMsgInfo ** __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0047ffb9;
    }
  }
  iVar2 = *piVar1;
LAB_0047ffb9:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (AudMsgInfo **)(*(int *)&this->field_0x4 + 8);
}
