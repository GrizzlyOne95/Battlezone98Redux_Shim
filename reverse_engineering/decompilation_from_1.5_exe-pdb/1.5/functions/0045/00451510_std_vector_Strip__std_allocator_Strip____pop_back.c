/*
 * Entry: 00451510
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::pop_back
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void pop_back(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::pop_back
          (vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
