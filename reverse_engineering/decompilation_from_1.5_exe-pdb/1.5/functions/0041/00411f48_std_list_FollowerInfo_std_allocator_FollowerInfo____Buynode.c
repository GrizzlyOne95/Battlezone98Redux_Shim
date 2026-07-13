/*
 * Entry: 00411f48
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Buynode
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: _Node * _Buynode(list<FollowerInfo,std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Buynode
          (list<FollowerInfo,std::allocator<FollowerInfo>_> *this)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = p_Var1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = p_Var1;
  }
  return p_Var1;
}
