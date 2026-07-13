/*
 * Entry: 0055767e
 * Name: std::_Vector_iterator<Session_*,std::allocator<Session_*>_>::operator*
 * Namespace: std::_Vector_iterator<Session_*,std::allocator<Session_*>_>
 * Signature: Session * * operator*(_Vector_iterator<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __thiscall
std::_Vector_iterator<Session_*,std::allocator<Session_*>_>::operator*
          (_Vector_iterator<Session_*,std::allocator<Session_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0055506d;
    }
  }
  iVar2 = *piVar1;
LAB_0055506d:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(Session ***)&this->field_0x4;
}
