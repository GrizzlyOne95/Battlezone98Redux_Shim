/*
 * Entry: 00411f31
 * Name: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Tidy
 * Namespace: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>
 * Signature: void _Tidy(list<FollowGroup_*,std::allocator<FollowGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Tidy
          (list<FollowGroup_*,std::allocator<FollowGroup_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
