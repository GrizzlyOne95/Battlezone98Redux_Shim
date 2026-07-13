/*
 * Entry: 004c7d74
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Iterator<1>::operator++
          (_Iterator<1> *this)

{
  list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
