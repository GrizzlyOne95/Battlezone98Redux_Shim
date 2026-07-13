/*
 * Entry: 0040e189
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Iterator<1>
 * Signature: AttackGroup * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AttackGroup ** __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0040df87;
    }
  }
  iVar2 = *piVar1;
LAB_0040df87:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (AttackGroup **)(*(int *)&this->field_0x4 + 8);
}
