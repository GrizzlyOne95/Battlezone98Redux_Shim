/*
 * Entry: 005550e9
 * Name: std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
 * Signature: PortData * * operator*(_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __thiscall
std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator*
          (_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00555107;
    }
  }
  iVar2 = *piVar1;
LAB_00555107:
  if (*(PortData ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
