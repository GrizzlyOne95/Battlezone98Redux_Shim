/*
 * Entry: 0047c8b5
 * Name: std::_Container_base_aux_alloc_real<std::allocator<Craft_*>_>::~_Container_base_aux_alloc_real<std::allocator<Craft_*>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<Craft_*>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<Craft_*>_>(_Container_base_aux_alloc_real<std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<Craft_*>_>::
~_Container_base_aux_alloc_real<std::allocator<Craft_*>_>
          (_Container_base_aux_alloc_real<std::allocator<Craft_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
