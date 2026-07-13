/*
 * Entry: 0053345d
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Buynode
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: _Node * _Buynode(list<Ordnance_*,std::allocator<Ordnance_*>_> * this, _Node * param_1, _Node * param_2, Ordnance * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Buynode
          (list<Ordnance_*,std::allocator<Ordnance_*>_> *this,_Node *param_1,_Node *param_2,
          Ordnance **param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<Ordnance_*,std::allocator<Ordnance_*>_>::_Node>(1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  if (&p_Var1->_Myval != (Ordnance **)0x0) {
    p_Var1->_Myval = *param_3;
  }
  return p_Var1;
}
