/*
 * Entry: 004e0fa4
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Max
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
 * Signature: _Node * _Max(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __cdecl
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
::_Max(_Node *param_1)

{
  _Node *p_Var1;
  
  do {
    p_Var1 = param_1;
    param_1 = p_Var1->_Right;
  } while (param_1->_Isnil == '\0');
  return p_Var1;
}
