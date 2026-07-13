/*
 * Entry: 004c7a8e
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::operator*
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>
 * Signature: DisplayViewInfo * * operator*(_Const_iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DisplayViewInfo ** __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::operator*
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
      goto LAB_004c7aac;
    }
  }
  iVar2 = *piVar1;
LAB_004c7aac:
  if (this->_Ptr == *(_Node **)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return &this->_Ptr->_Myval;
}
