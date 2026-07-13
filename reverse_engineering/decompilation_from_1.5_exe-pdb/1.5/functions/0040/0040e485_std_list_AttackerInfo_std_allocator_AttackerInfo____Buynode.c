/*
 * Entry: 0040e485
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Buynode
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: _Node * _Buynode(list<AttackerInfo,std::allocator<AttackerInfo>_> * this, _Node * param_1, _Node * param_2, AttackerInfo * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Buynode
          (list<AttackerInfo,std::allocator<AttackerInfo>_> *this,_Node *param_1,_Node *param_2,
          AttackerInfo *param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  _Construct<AttackerInfo,AttackerInfo>(&p_Var1->_Myval,param_3);
  return p_Var1;
}
