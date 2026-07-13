/*
 * Entry: 0040e4bf
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Buynode
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Signature: _Node * _Buynode(list<AttackGroup_*,std::allocator<AttackGroup_*>_> * this, _Node * param_1, _Node * param_2, AttackGroup * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Buynode
          (list<AttackGroup_*,std::allocator<AttackGroup_*>_> *this,_Node *param_1,_Node *param_2,
          AttackGroup **param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  if (&p_Var1->_Myval != (AttackGroup **)0x0) {
    p_Var1->_Myval = *param_3;
  }
  return p_Var1;
}
