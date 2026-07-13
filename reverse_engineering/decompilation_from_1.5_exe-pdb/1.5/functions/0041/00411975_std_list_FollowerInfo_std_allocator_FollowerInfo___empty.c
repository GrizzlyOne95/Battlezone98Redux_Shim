/*
 * Entry: 00411975
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::empty
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: bool empty(list<FollowerInfo,std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::empty
          (list<FollowerInfo,std::allocator<FollowerInfo>_> *this)

{
  return this->_Mysize == 0;
}
