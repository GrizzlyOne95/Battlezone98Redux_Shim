/*
 * Entry: 0055544e
 * Name: std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator+=
 * Namespace: std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>
 * Signature: _Vector_const_iterator<Server_*,std::allocator<Server_*>_> * operator+=(_Vector_const_iterator<Server_*,std::allocator<Server_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<Server_*,std::allocator<Server_*>_> * __thiscall
std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator+=
          (_Vector_const_iterator<Server_*,std::allocator<Server_*>_> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 != (int *)0x0) goto LAB_00555467;
    iVar2 = 0;
  }
  else {
LAB_00555467:
    iVar2 = *piVar1;
  }
  if (this->_Myptr + param_1 <= *(Server ***)(iVar2 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1;
    }
    if (*(Server ***)(iVar2 + 0xc) <= this->_Myptr + param_1) goto LAB_0055548f;
  }
  _invalid_parameter_noinfo();
LAB_0055548f:
  this->_Myptr = this->_Myptr + param_1;
  return this;
}
