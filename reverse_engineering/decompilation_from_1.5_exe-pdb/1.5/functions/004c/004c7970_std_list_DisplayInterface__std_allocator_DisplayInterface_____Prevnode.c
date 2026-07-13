/*
 * Entry: 004c7970
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Prevnode
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Signature: _Node * * _Prevnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Prevnode(_Node *param_1)

{
  return &param_1->_Prev;
}
