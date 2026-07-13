/*
 * Entry: 00450de0
 * Name: std::_Vector_val<Strip_*,std::allocator<Strip_*>_>::~_Vector_val<Strip_*,std::allocator<Strip_*>_>
 * Namespace: std::_Vector_val<Strip_*,std::allocator<Strip_*>_>
 * Signature: void ~_Vector_val<Strip_*,std::allocator<Strip_*>_>(_Vector_val<Strip_*,std::allocator<Strip_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Strip_*,std::allocator<Strip_*>_>::~_Vector_val<Strip_*,std::allocator<Strip_*>_>
          (_Vector_val<Strip_*,std::allocator<Strip_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
