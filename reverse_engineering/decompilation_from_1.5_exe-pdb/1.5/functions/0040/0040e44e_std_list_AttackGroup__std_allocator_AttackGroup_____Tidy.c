/*
 * Entry: 0040e44e
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Tidy
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Signature: void _Tidy(list<AttackGroup_*,std::allocator<AttackGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Tidy
          (list<AttackGroup_*,std::allocator<AttackGroup_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
