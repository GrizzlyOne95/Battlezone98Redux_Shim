/*
 * Entry: 00462401
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Init
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
 * Signature: void _Init(_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::_Init(_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
        *this)

{
  _Node **pp_Var1;
  _Node *p_Var2;
  
  p_Var2 = _Buynode(this);
  pp_Var1 = &this->_Myhead;
  *pp_Var1 = p_Var2;
  p_Var2->_Isnil = '\x01';
  (*pp_Var1)->_Parent = *pp_Var1;
  (*pp_Var1)->_Left = *pp_Var1;
  (*pp_Var1)->_Right = *pp_Var1;
  this->_Mysize = 0;
  return;
}
