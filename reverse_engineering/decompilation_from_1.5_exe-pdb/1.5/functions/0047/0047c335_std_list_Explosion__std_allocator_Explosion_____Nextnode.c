/*
 * Entry: 0047c335
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::_Nextnode
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: _Node * * _Nextnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl std::list<Explosion_*,std::allocator<Explosion_*>_>::_Nextnode(_Node *param_1)

{
  return &param_1->_Next;
}
