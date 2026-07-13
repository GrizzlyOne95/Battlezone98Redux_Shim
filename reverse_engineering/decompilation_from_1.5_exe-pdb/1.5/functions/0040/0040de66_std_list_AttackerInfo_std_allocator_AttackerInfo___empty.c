/*
 * Entry: 0040de66
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::empty
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: bool empty(list<AttackerInfo,std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::empty
          (list<AttackerInfo,std::allocator<AttackerInfo>_> *this)

{
  return this->_Mysize == 0;
}
