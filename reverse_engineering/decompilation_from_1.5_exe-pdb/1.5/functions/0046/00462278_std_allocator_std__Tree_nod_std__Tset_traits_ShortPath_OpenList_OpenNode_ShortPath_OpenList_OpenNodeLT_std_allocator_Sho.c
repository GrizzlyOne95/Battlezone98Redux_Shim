/*
 * Entry: 00462278
 * Name: std::allocator<std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node>::allocate
 * Namespace: std::allocator<std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node>
 * Signature: _Node * allocate(allocator<std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
allocator<std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node>
::allocate(allocator<std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node>
           *this,uint param_1)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_Tree_nod<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Node>
                     (param_1,(_Node *)0x0);
  return p_Var1;
}
