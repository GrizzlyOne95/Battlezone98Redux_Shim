/*
 * Entry: 0047ff4a
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Nextnode
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: _Node * * _Nextnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Nextnode(_Node *param_1)

{
  return &param_1->_Next;
}
