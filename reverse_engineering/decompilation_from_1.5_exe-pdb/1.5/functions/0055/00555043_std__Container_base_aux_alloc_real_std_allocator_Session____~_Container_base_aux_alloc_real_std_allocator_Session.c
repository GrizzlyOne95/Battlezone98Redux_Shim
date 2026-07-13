/*
 * Entry: 00555043
 * Name: std::_Container_base_aux_alloc_real<std::allocator<Session_*>_>::~_Container_base_aux_alloc_real<std::allocator<Session_*>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<Session_*>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<Session_*>_>(_Container_base_aux_alloc_real<std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<Session_*>_>::
~_Container_base_aux_alloc_real<std::allocator<Session_*>_>
          (_Container_base_aux_alloc_real<std::allocator<Session_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
