/*
 * Entry: 0047ca8f
 * Name: std::_Vector_val<Craft_*,std::allocator<Craft_*>_>::~_Vector_val<Craft_*,std::allocator<Craft_*>_>
 * Namespace: std::_Vector_val<Craft_*,std::allocator<Craft_*>_>
 * Signature: void ~_Vector_val<Craft_*,std::allocator<Craft_*>_>(_Vector_val<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Craft_*,std::allocator<Craft_*>_>::~_Vector_val<Craft_*,std::allocator<Craft_*>_>
          (_Vector_val<Craft_*,std::allocator<Craft_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
