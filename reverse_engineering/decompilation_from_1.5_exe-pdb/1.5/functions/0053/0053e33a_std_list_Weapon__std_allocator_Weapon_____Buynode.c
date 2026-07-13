/*
 * Entry: 0053e33a
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Buynode
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: _Node * _Buynode(list<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Buynode
          (list<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<Weapon_*,std::allocator<Weapon_*>_>::_Node>(1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = p_Var1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = p_Var1;
  }
  return p_Var1;
}
