/*
 * Entry: 00535280
 * Name: std::_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::~_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Namespace: std::_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: void ~_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>(_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
~_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
          (_Vector_val<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
