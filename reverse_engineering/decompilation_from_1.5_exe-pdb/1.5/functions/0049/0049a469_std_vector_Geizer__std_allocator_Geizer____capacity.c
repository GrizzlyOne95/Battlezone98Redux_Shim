/*
 * Entry: 0049a469
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::capacity
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: uint capacity(vector<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::capacity
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  if (this->_Myfirst == (Geizer **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
