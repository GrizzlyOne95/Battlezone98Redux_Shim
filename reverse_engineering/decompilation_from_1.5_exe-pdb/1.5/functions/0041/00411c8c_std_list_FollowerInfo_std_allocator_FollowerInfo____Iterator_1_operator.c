/*
 * Entry: 00411c8c
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>::operator*
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>
 * Signature: FollowerInfo * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FollowerInfo * __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00411aa1;
    }
  }
  iVar2 = *piVar1;
LAB_00411aa1:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (FollowerInfo *)(*(int *)&this->field_0x4 + 8);
}
