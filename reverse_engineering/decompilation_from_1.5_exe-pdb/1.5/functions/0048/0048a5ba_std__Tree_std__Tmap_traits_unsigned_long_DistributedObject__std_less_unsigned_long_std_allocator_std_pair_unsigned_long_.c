/*
 * Entry: 0048a5ba
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator::operator*
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator
 * Signature: pair<unsigned_long_const_,DistributedObject_*> * operator*(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_long_const_,DistributedObject_*> * __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::const_iterator::operator*(const_iterator *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0048a5d8;
    }
  }
  iVar2 = *piVar1;
LAB_0048a5d8:
  if (this->_Ptr == *(_Node **)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return &this->_Ptr->_Myval;
}
