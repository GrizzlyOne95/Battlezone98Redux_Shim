/*
 * Entry: 0048a4d9
 * Name: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Nextnode
 * Namespace: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
 * Signature: _Node * * _Nextnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl
std::
list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
::_Nextnode(_Node *param_1)

{
  return &param_1->_Next;
}
