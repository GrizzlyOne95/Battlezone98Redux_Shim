/*
 * Entry: 0048a74a
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator::_Dec
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator
 * Signature: void _Dec(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::const_iterator::_Dec(const_iterator *this)

{
  _Node *p_Var1;
  _Node *p_Var2;
  
  if (this->_padding_ == 0) {
    _invalid_parameter_noinfo();
  }
  p_Var2 = this->_Ptr;
  if (p_Var2->_Isnil == '\0') {
    p_Var1 = p_Var2->_Left;
    if (p_Var2->_Left->_Isnil == '\0') {
      do {
        p_Var2 = p_Var1;
        p_Var1 = p_Var2->_Right;
      } while (p_Var1->_Isnil == '\0');
      this->_Ptr = p_Var2;
      return;
    }
    while ((p_Var2 = p_Var2->_Parent, p_Var2->_Isnil == '\0' && (this->_Ptr == p_Var2->_Left))) {
      this->_Ptr = p_Var2;
    }
    if (this->_Ptr->_Isnil == '\0') {
      this->_Ptr = p_Var2;
      return;
    }
  }
  else {
    p_Var2 = p_Var2->_Right;
    this->_Ptr = p_Var2;
    if (p_Var2->_Isnil == '\0') {
      return;
    }
  }
  _invalid_parameter_noinfo();
  return;
}
