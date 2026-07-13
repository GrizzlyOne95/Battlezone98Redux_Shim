/*
 * Entry: 0040e581
 * Name: std::_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>::~_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Namespace: std::_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Signature: void ~_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>(_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>::
~_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>
          (_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
