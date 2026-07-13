/*
 * Entry: 005331b7
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>::operator--
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator--(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>::operator--(_Iterator<1> *this)

{
  list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator--
            ((_Const_iterator<1> *)this);
  return this;
}
