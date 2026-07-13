/*
 * Entry: 0048680b
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::capacity
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: uint capacity(vector<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::capacity
          (vector<Craft_*,std::allocator<Craft_*>_> *this)

{
  if (this->_Myfirst == (Craft **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
