/*
 * Entry: 00411fb7
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Buynode
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: _Node * _Buynode(list<FollowerInfo,std::allocator<FollowerInfo>_> * this, _Node * param_1, _Node * param_2, FollowerInfo * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Buynode
          (list<FollowerInfo,std::allocator<FollowerInfo>_> *this,_Node *param_1,_Node *param_2,
          FollowerInfo *param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  _Construct<FollowerInfo,FollowerInfo>(&p_Var1->_Myval,param_3);
  return p_Var1;
}
