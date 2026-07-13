/*
 * Entry: 00462107
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator::_Dec
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator
 * Signature: void _Dec(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
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
