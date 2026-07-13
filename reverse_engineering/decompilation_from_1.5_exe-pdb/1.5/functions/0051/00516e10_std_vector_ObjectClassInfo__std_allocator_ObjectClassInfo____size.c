/*
 * Entry: 00516e10
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::size
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: uint size(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::size
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
