/*
 * Entry: 0053e48e
 * Name: std::_List_ptr<Weapon_*,std::allocator<Weapon_*>_>::~_List_ptr<Weapon_*,std::allocator<Weapon_*>_>
 * Namespace: std::_List_ptr<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: void ~_List_ptr<Weapon_*,std::allocator<Weapon_*>_>(_List_ptr<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<Weapon_*,std::allocator<Weapon_*>_>::~_List_ptr<Weapon_*,std::allocator<Weapon_*>_>
          (_List_ptr<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
