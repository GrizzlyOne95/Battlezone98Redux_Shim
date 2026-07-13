/*
 * Entry: 004ada7f
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::size
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: uint size(vector<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::size
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
