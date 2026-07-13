/*
 * Entry: 004042f3
 * Name: std::list<AiTask_*,std::allocator<AiTask_*>_>::_Buynode
 * Namespace: std::list<AiTask_*,std::allocator<AiTask_*>_>
 * Signature: _Node * _Buynode(list<AiTask_*,std::allocator<AiTask_*>_> * this, _Node * param_1, _Node * param_2, AiTask * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<AiTask_*,std::allocator<AiTask_*>_>::_Buynode
          (list<AiTask_*,std::allocator<AiTask_*>_> *this,_Node *param_1,_Node *param_2,
          AiTask **param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<AiTask_*,std::allocator<AiTask_*>_>::_Node>(1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  if (&p_Var1->_Myval != (AiTask **)0x0) {
    p_Var1->_Myval = *param_3;
  }
  return p_Var1;
}
