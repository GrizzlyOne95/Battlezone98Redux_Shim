/*
 * Entry: 0053e355
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Tidy
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: void _Tidy(list<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Tidy(list<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
