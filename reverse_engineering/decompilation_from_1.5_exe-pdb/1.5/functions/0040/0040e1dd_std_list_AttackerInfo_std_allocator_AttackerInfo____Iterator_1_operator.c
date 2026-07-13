/*
 * Entry: 0040e1dd
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Iterator<1>::operator++
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
