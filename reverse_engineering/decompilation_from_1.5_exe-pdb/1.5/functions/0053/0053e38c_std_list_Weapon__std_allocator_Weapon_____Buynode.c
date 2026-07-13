/*
 * Entry: 0053e38c
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Buynode
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: _Node * _Buynode(list<Weapon_*,std::allocator<Weapon_*>_> * this, _Node * param_1, _Node * param_2, Weapon * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Buynode
          (list<Weapon_*,std::allocator<Weapon_*>_> *this,_Node *param_1,_Node *param_2,
          Weapon **param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<Weapon_*,std::allocator<Weapon_*>_>::_Node>(1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  if (&p_Var1->_Myval != (Weapon **)0x0) {
    p_Var1->_Myval = *param_3;
  }
  return p_Var1;
}
