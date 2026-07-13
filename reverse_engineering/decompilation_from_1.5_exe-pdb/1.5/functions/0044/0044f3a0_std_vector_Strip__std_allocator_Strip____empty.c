/*
 * Entry: 0044f3a0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::empty
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: bool empty(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::empty(vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
