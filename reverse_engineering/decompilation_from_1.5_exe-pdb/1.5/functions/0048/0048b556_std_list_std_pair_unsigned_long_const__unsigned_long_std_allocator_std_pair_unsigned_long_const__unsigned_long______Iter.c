/*
 * Entry: 0048b556
 * Name: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>::operator--
 * Namespace: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator--(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::
list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
::_Iterator<1>::operator--(_Iterator<1> *this)

{
  list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::_Const_iterator<1>::operator--((_Const_iterator<1> *)this);
  return this;
}
