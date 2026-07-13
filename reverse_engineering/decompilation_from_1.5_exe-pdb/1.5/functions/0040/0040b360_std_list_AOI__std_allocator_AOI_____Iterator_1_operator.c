/*
 * Entry: 0040b360
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++((_Const_iterator<1> *)this);
  return this;
}
