/*
 * Entry: 004b0b05
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator*
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>
 * Signature: RtimeClass * * operator*(_Const_iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RtimeClass ** __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator*
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
      goto LAB_004b0b23;
    }
  }
  iVar2 = *piVar1;
LAB_004b0b23:
  if (this->_Ptr == *(_Node **)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return &this->_Ptr->_Myval;
}
