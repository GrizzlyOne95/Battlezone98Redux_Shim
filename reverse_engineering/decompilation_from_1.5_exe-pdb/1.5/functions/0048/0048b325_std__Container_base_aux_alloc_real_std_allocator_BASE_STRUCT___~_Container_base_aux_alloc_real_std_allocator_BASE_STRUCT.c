/*
 * Entry: 0048b325
 * Name: std::_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_>::~_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_>(_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_>::
~_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_>
          (_Container_base_aux_alloc_real<std::allocator<BASE_STRUCT>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
