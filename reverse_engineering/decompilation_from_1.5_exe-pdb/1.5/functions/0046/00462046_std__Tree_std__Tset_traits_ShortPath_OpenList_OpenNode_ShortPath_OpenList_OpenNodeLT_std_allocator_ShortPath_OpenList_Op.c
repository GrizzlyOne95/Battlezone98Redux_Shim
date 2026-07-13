/*
 * Entry: 00462046
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator::operator*
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator
 * Signature: OpenNode * operator*(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OpenNode * __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
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
      goto LAB_00462064;
    }
  }
  iVar2 = *piVar1;
LAB_00462064:
  if (this->_Ptr == *(_Node **)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return &this->_Ptr->_Myval;
}
