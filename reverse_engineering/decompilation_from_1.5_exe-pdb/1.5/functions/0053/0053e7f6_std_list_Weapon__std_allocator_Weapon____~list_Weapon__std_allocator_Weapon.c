/*
 * Entry: 0053e7f6
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::~list<Weapon_*,std::allocator<Weapon_*>_>
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: void ~list<Weapon_*,std::allocator<Weapon_*>_>(list<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::~list<Weapon_*,std::allocator<Weapon_*>_>
          (list<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
