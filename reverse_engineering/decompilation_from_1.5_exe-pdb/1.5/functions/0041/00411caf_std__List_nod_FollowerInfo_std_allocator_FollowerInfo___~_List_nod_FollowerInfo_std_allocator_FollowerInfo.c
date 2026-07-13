/*
 * Entry: 00411caf
 * Name: std::_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>::~_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>
 * Namespace: std::_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: void ~_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>(_List_nod<FollowerInfo,std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>::
~_List_nod<FollowerInfo,std::allocator<FollowerInfo>_>
          (_List_nod<FollowerInfo,std::allocator<FollowerInfo>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
