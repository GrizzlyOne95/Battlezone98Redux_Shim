/*
 * Entry: 00496a67
 * Name: std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator++
 * Namespace: std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> * operator++(_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> * __thiscall
std::_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator++
          (_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00496a85;
    }
  }
  iVar2 = *piVar1;
LAB_00496a85:
  if (*(Scanner ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  this->_Myptr = this->_Myptr + 1;
  return this;
}
