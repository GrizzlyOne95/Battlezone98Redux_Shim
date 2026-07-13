/*
 * Entry: 00405a42
 * Name: std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * operator*(_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
          (_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00405a60;
    }
  }
  iVar2 = *piVar1;
LAB_00405a60:
  if (*(GameObject ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
