/*
 * Entry: 004152ca
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::size
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: uint size(vector<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::size(vector<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
