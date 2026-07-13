/*
 * Entry: 0046222b
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator::const_iterator
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::const_iterator
 * Signature: const_iterator * const_iterator(const_iterator * this, _Node * param_1, _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

const_iterator * __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::const_iterator::const_iterator
          (const_iterator *this,_Node *param_1,
          _Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
          *param_2)

{
  this->_padding_ = 0;
  this->_Ptr = param_1;
  if (param_2 ==
      (_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
       *)0x0) {
    _invalid_parameter_noinfo();
  }
  this->_padding_ = param_2->_padding_;
  return this;
}
