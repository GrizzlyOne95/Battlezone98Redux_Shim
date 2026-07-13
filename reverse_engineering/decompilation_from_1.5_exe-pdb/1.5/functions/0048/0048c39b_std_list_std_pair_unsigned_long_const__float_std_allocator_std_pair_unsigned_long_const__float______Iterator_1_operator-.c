/*
 * Entry: 0048c39b
 * Name: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Iterator<1>::operator->
 * Namespace: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Iterator<1>
 * Signature: pair<unsigned_long_const_,float> * operator->(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_long_const_,float> * __thiscall
std::
list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
::_Iterator<1>::operator->(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0048b386;
    }
  }
  iVar2 = *piVar1;
LAB_0048b386:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (pair<unsigned_long_const_,float> *)(*(int *)&this->field_0x4 + 8);
}
