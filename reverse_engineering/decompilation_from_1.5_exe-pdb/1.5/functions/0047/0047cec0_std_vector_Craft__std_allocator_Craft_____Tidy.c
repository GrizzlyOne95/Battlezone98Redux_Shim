/*
 * Entry: 0047cec0
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::_Tidy
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: void _Tidy(vector<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::_Tidy(vector<Craft_*,std::allocator<Craft_*>_> *this)

{
  if (this->_Myfirst != (Craft **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Craft **)0x0;
  this->_Mylast = (Craft **)0x0;
  this->_Myend = (Craft **)0x0;
  return;
}
