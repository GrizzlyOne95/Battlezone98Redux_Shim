/*
 * Entry: 00405c97
 * Name: std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: Geizer * * operator*(_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __thiscall
std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator*
          (_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00405cb5;
    }
  }
  iVar2 = *piVar1;
LAB_00405cb5:
  if (*(Geizer ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
