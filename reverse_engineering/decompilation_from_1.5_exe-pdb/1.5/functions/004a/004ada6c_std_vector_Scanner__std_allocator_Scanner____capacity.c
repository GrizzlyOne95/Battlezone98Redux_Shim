/*
 * Entry: 004ada6c
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::capacity
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: uint capacity(vector<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::capacity
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  if (this->_Myfirst == (Scanner **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
