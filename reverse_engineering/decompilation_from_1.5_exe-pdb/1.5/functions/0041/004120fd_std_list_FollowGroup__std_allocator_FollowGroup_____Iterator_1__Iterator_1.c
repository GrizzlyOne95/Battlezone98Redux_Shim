/*
 * Entry: 004120fd
 * Name: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>::_Iterator<1>
 * Namespace: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * _Iterator<1>(_Iterator<1> * this, _Node * param_1, list<FollowGroup_*,std::allocator<FollowGroup_*>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Iterator<1>::_Iterator<1>
          (_Iterator<1> *this,_Node *param_1,
          list<FollowGroup_*,std::allocator<FollowGroup_*>_> *param_2)

{
  list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)this,param_1,param_2);
  return this;
}
