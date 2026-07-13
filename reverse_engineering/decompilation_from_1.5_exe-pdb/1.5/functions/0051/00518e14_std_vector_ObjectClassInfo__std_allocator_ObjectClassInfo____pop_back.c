/*
 * Entry: 00518e14
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::pop_back
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: void pop_back(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::pop_back
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
