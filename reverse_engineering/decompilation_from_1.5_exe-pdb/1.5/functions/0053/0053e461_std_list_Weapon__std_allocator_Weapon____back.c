/*
 * Entry: 0053e461
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::back
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: Weapon * * back(list<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon ** __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::back(list<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  Weapon **ppWVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  ppWVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppWVar1;
}
