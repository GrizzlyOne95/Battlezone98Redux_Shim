/*
 * Entry: 004152d4
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::empty
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: bool empty(vector<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::empty(vector<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
