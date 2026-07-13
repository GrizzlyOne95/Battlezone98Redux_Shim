/*
 * Entry: 00411cb8
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Tidy
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: void _Tidy(list<FollowerInfo,std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Tidy
          (list<FollowerInfo,std::allocator<FollowerInfo>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
