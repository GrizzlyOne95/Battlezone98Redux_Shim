/*
 * Entry: 0053e331
 * Name: std::_List_nod<Weapon_*,std::allocator<Weapon_*>_>::~_List_nod<Weapon_*,std::allocator<Weapon_*>_>
 * Namespace: std::_List_nod<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: void ~_List_nod<Weapon_*,std::allocator<Weapon_*>_>(_List_nod<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<Weapon_*,std::allocator<Weapon_*>_>::~_List_nod<Weapon_*,std::allocator<Weapon_*>_>
          (_List_nod<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
