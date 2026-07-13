/*
 * Entry: 004022fd
 * Name: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Buynode
 * Namespace: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Signature: _Node * _Buynode(list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Buynode
          (list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *this)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = p_Var1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = p_Var1;
  }
  return p_Var1;
}
