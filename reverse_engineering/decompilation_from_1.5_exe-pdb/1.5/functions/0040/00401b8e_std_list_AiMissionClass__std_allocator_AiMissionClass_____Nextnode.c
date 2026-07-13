/*
 * Entry: 00401b8e
 * Name: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Nextnode
 * Namespace: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Signature: _Node * * _Nextnode(_Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node ** __cdecl
std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Nextnode(_Node *param_1)

{
  return &param_1->_Next;
}
