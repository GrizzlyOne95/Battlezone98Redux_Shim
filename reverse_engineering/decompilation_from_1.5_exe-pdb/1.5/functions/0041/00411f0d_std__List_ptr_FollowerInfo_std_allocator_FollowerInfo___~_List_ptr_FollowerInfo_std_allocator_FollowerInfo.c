/*
 * Entry: 00411f0d
 * Name: std::_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_>::~_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_>
 * Namespace: std::_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: void ~_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_>(_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_>::
~_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_>
          (_List_ptr<FollowerInfo,std::allocator<FollowerInfo>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
