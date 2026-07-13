/*
 * Entry: 0048bb38
 * Name: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>::operator*
 * Namespace: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>
 * Signature: pair<unsigned_long_const_,unsigned_long> * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_long_const_,unsigned_long> * __thiscall
std::
list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
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
      goto LAB_0048b4c7;
    }
  }
  iVar2 = *piVar1;
LAB_0048b4c7:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (pair<unsigned_long_const_,unsigned_long> *)(*(int *)&this->field_0x4 + 8);
}
