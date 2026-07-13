/*
 * Entry: 0048a3ab
 * Name: std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator++
 * Namespace: std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * operator++(_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * __thiscall
std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator++
          (_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0048a3c9;
    }
  }
  iVar2 = *piVar1;
LAB_0048a3c9:
  if (*(DistributedObject ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  this->_Myptr = this->_Myptr + 1;
  return this;
}
