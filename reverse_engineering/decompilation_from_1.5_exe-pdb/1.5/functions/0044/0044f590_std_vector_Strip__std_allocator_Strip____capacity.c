/*
 * Entry: 0044f590
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::capacity
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: uint capacity(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::capacity
          (vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  if (this->_Myfirst == (Strip **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
