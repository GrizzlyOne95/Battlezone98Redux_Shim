/*
 * Entry: 0044f660
 * Name: std::_Vector_const_iterator<Strip_*,std::allocator<Strip_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<Strip_*,std::allocator<Strip_*>_>
 * Signature: Strip * * operator*(_Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __thiscall
std::_Vector_const_iterator<Strip_*,std::allocator<Strip_*>_>::operator*
          (_Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0044f67e;
    }
  }
  iVar2 = *piVar1;
LAB_0044f67e:
  if (*(Strip ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
    return this->_Myptr;
  }
  return this->_Myptr;
}
