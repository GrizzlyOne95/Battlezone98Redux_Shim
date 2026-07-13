/*
 * Entry: 004a0911
 * Name: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Prevnode
 * Namespace: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
 * Signature: _Node * * _Prevnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl
std::
list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
::_Prevnode(_Node *param_1)

{
  return &param_1->_Prev;
}
