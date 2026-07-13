/*
 * Entry: 00516e1a
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::empty
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: bool empty(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::empty
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
