/*
 * Entry: 00411cdb
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>::operator++
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
