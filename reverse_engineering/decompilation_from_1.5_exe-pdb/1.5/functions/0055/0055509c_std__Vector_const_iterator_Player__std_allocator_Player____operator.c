/*
 * Entry: 0055509c
 * Name: std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>
 * Signature: Player * * operator*(_Vector_const_iterator<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __thiscall
std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*
          (_Vector_const_iterator<Player_*,std::allocator<Player_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_005550ba;
    }
  }
  iVar2 = *piVar1;
LAB_005550ba:
  if (*(Player ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
