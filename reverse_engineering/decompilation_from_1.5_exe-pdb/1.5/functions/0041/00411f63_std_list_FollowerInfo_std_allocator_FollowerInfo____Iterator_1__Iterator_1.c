/*
 * Entry: 00411f63
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>::_Iterator<1>
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>
 * Signature: _Iterator<1> * _Iterator<1>(_Iterator<1> * this, _Node * param_1, list<FollowerInfo,std::allocator<FollowerInfo>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Iterator<1>::_Iterator<1>
          (_Iterator<1> *this,_Node *param_1,
          list<FollowerInfo,std::allocator<FollowerInfo>_> *param_2)

{
  list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)this,param_1,param_2);
  return this;
}
