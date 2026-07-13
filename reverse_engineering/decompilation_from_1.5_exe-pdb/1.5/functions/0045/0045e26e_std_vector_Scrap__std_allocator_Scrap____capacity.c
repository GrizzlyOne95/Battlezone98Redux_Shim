/*
 * Entry: 0045e26e
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::capacity
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: uint capacity(vector<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::capacity
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  if (this->_Myfirst == (Scrap **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
