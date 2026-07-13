/*
 * Entry: 0055525c
 * Name: std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++
 * Namespace: std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>
 * Signature: _Vector_const_iterator<Session_*,std::allocator<Session_*>_> * operator++(_Vector_const_iterator<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<Session_*,std::allocator<Session_*>_> * __thiscall
std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++
          (_Vector_const_iterator<Session_*,std::allocator<Session_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0055527a;
    }
  }
  iVar2 = *piVar1;
LAB_0055527a:
  if (*(Session ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  this->_Myptr = this->_Myptr + 1;
  return this;
}
