/*
 * Entry: 004a10d1
 * Name: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>::operator*
 * Namespace: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>
 * Signature: pair<unsigned_int_const_,char_const_*> * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_int_const_,char_const_*> * __thiscall
std::
list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004a107f;
    }
  }
  iVar2 = *piVar1;
LAB_004a107f:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (pair<unsigned_int_const_,char_const_*> *)(*(int *)&this->field_0x4 + 8);
}
