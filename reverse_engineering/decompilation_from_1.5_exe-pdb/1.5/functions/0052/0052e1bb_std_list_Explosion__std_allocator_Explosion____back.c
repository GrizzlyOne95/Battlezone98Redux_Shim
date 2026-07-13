/*
 * Entry: 0052e1bb
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::back
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: Explosion * * back(list<Explosion_*,std::allocator<Explosion_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion ** __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::back
          (list<Explosion_*,std::allocator<Explosion_*>_> *this)

{
  Explosion **ppEVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  ppEVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppEVar1;
}
