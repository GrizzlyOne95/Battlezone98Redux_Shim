/*
 * Entry: 00516ea4
 * Name: std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: ObjectClassInfo * * operator*(_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __thiscall
std::_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator*
          (_Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00516ec2;
    }
  }
  iVar2 = *piVar1;
LAB_00516ec2:
  if (*(ObjectClassInfo ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
