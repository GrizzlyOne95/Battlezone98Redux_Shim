/*
 * Entry: 0041228c
 * Name: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::~list<FollowGroup_*,std::allocator<FollowGroup_*>_>
 * Namespace: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>
 * Signature: void ~list<FollowGroup_*,std::allocator<FollowGroup_*>_>(list<FollowGroup_*,std::allocator<FollowGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::
~list<FollowGroup_*,std::allocator<FollowGroup_*>_>
          (list<FollowGroup_*,std::allocator<FollowGroup_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
