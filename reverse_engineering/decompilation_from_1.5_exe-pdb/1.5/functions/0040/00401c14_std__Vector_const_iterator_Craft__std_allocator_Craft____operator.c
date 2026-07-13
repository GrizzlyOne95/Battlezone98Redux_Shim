/*
 * Entry: 00401c14
 * Name: std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++
 * Namespace: std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
 * Signature: _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> * operator++(_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> * __thiscall
std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++
          (_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00401c32;
    }
  }
  iVar2 = *piVar1;
LAB_00401c32:
  if (*(Craft ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  this->_Myptr = this->_Myptr + 1;
  return this;
}
