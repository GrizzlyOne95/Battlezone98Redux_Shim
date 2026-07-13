/*
 * Entry: 00411c72
 * Name: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>
 * Signature: FollowGroup * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FollowGroup ** __thiscall
std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00411a48;
    }
  }
  iVar2 = *piVar1;
LAB_00411a48:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (FollowGroup **)(*(int *)&this->field_0x4 + 8);
}
