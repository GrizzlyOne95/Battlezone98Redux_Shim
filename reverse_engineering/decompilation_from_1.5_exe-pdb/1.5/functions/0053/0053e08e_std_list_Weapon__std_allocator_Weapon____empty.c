/*
 * Entry: 0053e08e
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::empty
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: bool empty(list<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::empty(list<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  return this->_Mysize == 0;
}
