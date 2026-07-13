/*
 * Entry: 00461d01
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Max
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
 * Signature: _Node * _Max(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __cdecl
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::_Max(_Node *param_1)

{
  _Node *p_Var1;
  
  do {
    p_Var1 = param_1;
    param_1 = p_Var1->_Right;
  } while (param_1->_Isnil == '\0');
  return p_Var1;
}
