/*
 * Entry: 004c7960
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Nextnode
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Signature: _Node * * _Nextnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Nextnode(_Node *param_1)

{
  return &param_1->_Next;
}
