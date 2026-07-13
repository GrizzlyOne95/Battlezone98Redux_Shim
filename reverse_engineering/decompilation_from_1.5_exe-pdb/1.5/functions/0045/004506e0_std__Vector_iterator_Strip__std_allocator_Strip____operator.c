/*
 * Entry: 004506e0
 * Name: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator*
 * Namespace: std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>
 * Signature: Strip * * operator*(_Vector_iterator<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall
std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>::operator*
          (_Vector_iterator<Strip_*,std::allocator<Strip_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004506fe;
    }
  }
  iVar2 = *piVar1;
LAB_004506fe:
  if (*(Strip ***)(iVar2 + 0x10) <= *(Strip ***)&this->field_0x4) {
    _invalid_parameter_noinfo();
    return *(Strip ***)&this->field_0x4;
  }
  return *(Strip ***)&this->field_0x4;
}
