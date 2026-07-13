/*
 * Entry: 005553be
 * Name: std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator+=
 * Namespace: std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
 * Signature: _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> * operator+=(_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> * __thiscall
std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator+=
          (_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 != (int *)0x0) goto LAB_005553d7;
    iVar2 = 0;
  }
  else {
LAB_005553d7:
    iVar2 = *piVar1;
  }
  if (this->_Myptr + param_1 <= *(PortData ***)(iVar2 + 0x10)) {
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1;
    }
    if (*(PortData ***)(iVar2 + 0xc) <= this->_Myptr + param_1) goto LAB_005553ff;
  }
  _invalid_parameter_noinfo();
LAB_005553ff:
  this->_Myptr = this->_Myptr + param_1;
  return this;
}
