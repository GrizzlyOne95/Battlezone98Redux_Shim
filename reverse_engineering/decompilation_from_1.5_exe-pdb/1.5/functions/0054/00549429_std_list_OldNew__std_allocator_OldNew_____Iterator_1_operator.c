/*
 * Entry: 00549429
 * Name: std::list<OldNew_*,std::allocator<OldNew_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<OldNew_*,std::allocator<OldNew_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<OldNew_*,std::allocator<OldNew_*>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
