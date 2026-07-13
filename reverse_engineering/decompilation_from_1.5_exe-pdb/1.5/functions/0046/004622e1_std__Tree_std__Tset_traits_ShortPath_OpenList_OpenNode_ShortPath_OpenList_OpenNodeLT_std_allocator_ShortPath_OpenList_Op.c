/*
 * Entry: 004622e1
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator::operator++
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::iterator
 * Signature: iterator * operator++(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator * __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::iterator::operator++(iterator *this)

{
  const_iterator::_Inc((const_iterator *)this);
  return this;
}
