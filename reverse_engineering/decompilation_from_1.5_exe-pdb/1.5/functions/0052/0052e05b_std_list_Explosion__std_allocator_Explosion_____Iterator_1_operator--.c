/*
 * Entry: 0052e05b
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::_Iterator<1>::operator--
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator--(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::_Iterator<1>::operator--(_Iterator<1> *this)

{
  list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator--
            ((_Const_iterator<1> *)this);
  return this;
}
