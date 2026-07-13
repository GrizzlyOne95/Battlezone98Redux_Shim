/*
 * Entry: 004ce79a
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::const_iterator::_Inc
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::const_iterator
 * Signature: void _Inc(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
::const_iterator::_Inc(const_iterator *this)

{
  _Node *p_Var1;
  _Node *p_Var2;
  
  if (this->_padding_ == 0) {
    _invalid_parameter_noinfo();
  }
  p_Var2 = this->_Ptr;
  if (p_Var2->_Isnil == '\0') {
    p_Var1 = p_Var2->_Right;
    if (p_Var2->_Right->_Isnil == '\0') {
      do {
        p_Var2 = p_Var1;
        p_Var1 = p_Var2->_Left;
      } while (p_Var1->_Isnil == '\0');
      this->_Ptr = p_Var2;
    }
    else {
      while ((p_Var2 = p_Var2->_Parent, p_Var2->_Isnil == '\0' && (this->_Ptr == p_Var2->_Right))) {
        this->_Ptr = p_Var2;
      }
      this->_Ptr = p_Var2;
    }
  }
  else {
    _invalid_parameter_noinfo();
  }
  return;
}
