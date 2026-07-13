/*
 * Entry: 004adef7
 * Name: std::_Vector_val<Scanner_*,std::allocator<Scanner_*>_>::~_Vector_val<Scanner_*,std::allocator<Scanner_*>_>
 * Namespace: std::_Vector_val<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: void ~_Vector_val<Scanner_*,std::allocator<Scanner_*>_>(_Vector_val<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Scanner_*,std::allocator<Scanner_*>_>::
~_Vector_val<Scanner_*,std::allocator<Scanner_*>_>
          (_Vector_val<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
