/*
 * Entry: 0047d076
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::~vector<Craft_*,std::allocator<Craft_*>_>
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: void ~vector<Craft_*,std::allocator<Craft_*>_>(vector<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::~vector<Craft_*,std::allocator<Craft_*>_>
          (vector<Craft_*,std::allocator<Craft_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
