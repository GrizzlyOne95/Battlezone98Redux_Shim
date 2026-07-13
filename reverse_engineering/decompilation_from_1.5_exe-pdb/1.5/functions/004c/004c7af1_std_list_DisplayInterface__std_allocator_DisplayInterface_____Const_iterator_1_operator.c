/*
 * Entry: 004c7af1
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::operator*
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>
 * Signature: DisplayInterface * * operator*(_Const_iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DisplayInterface ** __thiscall
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::operator*
          (_Const_iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004c7b0f;
    }
  }
  iVar2 = *piVar1;
LAB_004c7b0f:
  if (this->_Ptr == *(_Node **)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return &this->_Ptr->_Myval;
}
