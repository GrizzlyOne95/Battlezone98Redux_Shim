/*
 * Entry: 004122f1
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::~list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: void ~list<FollowerInfo,std::allocator<FollowerInfo>_>(list<FollowerInfo,std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::
~list<FollowerInfo,std::allocator<FollowerInfo>_>
          (list<FollowerInfo,std::allocator<FollowerInfo>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
