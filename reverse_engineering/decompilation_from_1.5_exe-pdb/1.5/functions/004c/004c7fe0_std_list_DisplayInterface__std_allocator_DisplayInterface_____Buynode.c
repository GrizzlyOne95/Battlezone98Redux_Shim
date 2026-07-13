/*
 * Entry: 004c7fe0
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Buynode
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Signature: _Node * _Buynode(list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Buynode
          (list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *this)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = p_Var1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = p_Var1;
  }
  return p_Var1;
}
