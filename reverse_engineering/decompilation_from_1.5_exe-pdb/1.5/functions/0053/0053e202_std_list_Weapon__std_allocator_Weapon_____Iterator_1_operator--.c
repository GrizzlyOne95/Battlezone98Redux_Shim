/*
 * Entry: 0053e202
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>::operator--
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator--(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>::operator--(_Iterator<1> *this)

{
  list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator--
            ((_Const_iterator<1> *)this);
  return this;
}
