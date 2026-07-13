/*
 * Entry: 00460c00
 * Name: std::_Vector_val<Scrap_*,std::allocator<Scrap_*>_>::~_Vector_val<Scrap_*,std::allocator<Scrap_*>_>
 * Namespace: std::_Vector_val<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: void ~_Vector_val<Scrap_*,std::allocator<Scrap_*>_>(_Vector_val<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Scrap_*,std::allocator<Scrap_*>_>::~_Vector_val<Scrap_*,std::allocator<Scrap_*>_>
          (_Vector_val<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
