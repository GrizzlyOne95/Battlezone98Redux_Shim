/*
 * Entry: 005550dd
 * Name: std::_Container_base_aux_alloc_real<std::allocator<PortData_*>_>::~_Container_base_aux_alloc_real<std::allocator<PortData_*>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<PortData_*>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<PortData_*>_>(_Container_base_aux_alloc_real<std::allocator<PortData_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<PortData_*>_>::
~_Container_base_aux_alloc_real<std::allocator<PortData_*>_>
          (_Container_base_aux_alloc_real<std::allocator<PortData_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
