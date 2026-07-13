/*
 * Entry: 0040e418
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Buynode
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: _Node * _Buynode(list<AttackerInfo,std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Buynode
          (list<AttackerInfo,std::allocator<AttackerInfo>_> *this)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<AttackerInfo,std::allocator<AttackerInfo>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = p_Var1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = p_Var1;
  }
  return p_Var1;
}
