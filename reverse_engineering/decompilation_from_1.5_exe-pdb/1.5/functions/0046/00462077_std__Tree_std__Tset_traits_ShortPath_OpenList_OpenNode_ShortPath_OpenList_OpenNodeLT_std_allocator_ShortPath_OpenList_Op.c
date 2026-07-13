/*
 * Entry: 00462077
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator::operator==
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator
 * Signature: bool operator==(const_iterator * this, const_iterator * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::const_iterator::operator==(const_iterator *this,const_iterator *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return (bool)('\x01' - (this->_Ptr != param_1->_Ptr));
}
