/*
 * Entry: 0044f390
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::size
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: uint size(vector<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::size(vector<Strip_*,std::allocator<Strip_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
