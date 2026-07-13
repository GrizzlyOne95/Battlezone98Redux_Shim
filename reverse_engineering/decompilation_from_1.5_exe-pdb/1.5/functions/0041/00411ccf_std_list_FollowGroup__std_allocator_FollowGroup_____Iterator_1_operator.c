/*
 * Entry: 00411ccf
 * Name: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>::operator++
          (_Iterator<1> *this)

{
  list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
