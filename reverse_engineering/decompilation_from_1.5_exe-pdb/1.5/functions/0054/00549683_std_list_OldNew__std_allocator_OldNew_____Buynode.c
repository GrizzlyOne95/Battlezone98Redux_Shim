/*
 * Entry: 00549683
 * Name: std::list<OldNew_*,std::allocator<OldNew_*>_>::_Buynode
 * Namespace: std::list<OldNew_*,std::allocator<OldNew_*>_>
 * Signature: _Node * _Buynode(list<OldNew_*,std::allocator<OldNew_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<OldNew_*,std::allocator<OldNew_*>_>::_Buynode
          (list<OldNew_*,std::allocator<OldNew_*>_> *this)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<OldNew_*,std::allocator<OldNew_*>_>::_Node>(1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = p_Var1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = p_Var1;
  }
  return p_Var1;
}
