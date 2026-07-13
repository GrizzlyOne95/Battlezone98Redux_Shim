/*
 * Entry: 005496b5
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::_Buynode
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>
 * Signature: _Node * _Buynode(list<Addr_*,std::allocator<Addr_*>_> * this, _Node * param_1, _Node * param_2, Addr * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<Addr_*,std::allocator<Addr_*>_>::_Buynode
          (list<Addr_*,std::allocator<Addr_*>_> *this,_Node *param_1,_Node *param_2,Addr **param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<Addr_*,std::allocator<Addr_*>_>::_Node>(1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  if (&p_Var1->_Myval != (Addr **)0x0) {
    p_Var1->_Myval = *param_3;
  }
  return p_Var1;
}
