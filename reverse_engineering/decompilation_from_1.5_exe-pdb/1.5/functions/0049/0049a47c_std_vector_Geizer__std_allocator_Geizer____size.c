/*
 * Entry: 0049a47c
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::size
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: uint size(vector<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::size
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
