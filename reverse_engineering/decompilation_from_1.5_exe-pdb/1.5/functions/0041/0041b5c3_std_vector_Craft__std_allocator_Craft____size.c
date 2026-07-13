/*
 * Entry: 0041b5c3
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::size
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: uint size(vector<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::size(vector<Craft_*,std::allocator<Craft_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
