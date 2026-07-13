/*
 * Entry: 0040df54
 * Name: std::_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_>::~_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_>(_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_>::
~_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_>
          (_Container_base_aux_alloc_real<std::allocator<AttackerInfo>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
