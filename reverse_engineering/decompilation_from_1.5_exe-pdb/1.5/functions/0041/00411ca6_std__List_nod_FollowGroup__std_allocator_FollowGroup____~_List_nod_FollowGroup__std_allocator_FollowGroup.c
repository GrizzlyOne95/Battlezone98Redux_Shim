/*
 * Entry: 00411ca6
 * Name: std::_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_>::~_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_>
 * Namespace: std::_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_>
 * Signature: void ~_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_>(_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_>::
~_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_>
          (_List_nod<FollowGroup_*,std::allocator<FollowGroup_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
