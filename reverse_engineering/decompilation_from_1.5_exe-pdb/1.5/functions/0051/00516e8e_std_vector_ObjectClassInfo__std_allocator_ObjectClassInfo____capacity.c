/*
 * Entry: 00516e8e
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::capacity
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: uint capacity(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::capacity
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  if (this->_Myfirst == (ObjectClassInfo **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
