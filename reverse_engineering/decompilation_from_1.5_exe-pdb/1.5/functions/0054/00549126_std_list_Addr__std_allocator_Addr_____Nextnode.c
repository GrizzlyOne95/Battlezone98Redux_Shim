/*
 * Entry: 00549126
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::_Nextnode
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>
 * Signature: _Node * * _Nextnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl std::list<Addr_*,std::allocator<Addr_*>_>::_Nextnode(_Node *param_1)

{
  return &param_1->_Next;
}
