/*
 * Entry: 004bfd0f
 * Name: std::_Container_base_aux_alloc_real<std::allocator<RadarItem>_>::~_Container_base_aux_alloc_real<std::allocator<RadarItem>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<RadarItem>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<RadarItem>_>(_Container_base_aux_alloc_real<std::allocator<RadarItem>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<RadarItem>_>::
~_Container_base_aux_alloc_real<std::allocator<RadarItem>_>
          (_Container_base_aux_alloc_real<std::allocator<RadarItem>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
