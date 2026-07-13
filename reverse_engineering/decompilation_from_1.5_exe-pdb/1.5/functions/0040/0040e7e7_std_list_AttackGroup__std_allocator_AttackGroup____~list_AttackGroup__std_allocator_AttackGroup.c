/*
 * Entry: 0040e7e7
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::~list<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Signature: void ~list<AttackGroup_*,std::allocator<AttackGroup_*>_>(list<AttackGroup_*,std::allocator<AttackGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::
~list<AttackGroup_*,std::allocator<AttackGroup_*>_>
          (list<AttackGroup_*,std::allocator<AttackGroup_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
