/*
 * Entry: 0040200d
 * Name: std::_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_>::~_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_>(_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_>::
~_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_>
          (_Container_base_aux_alloc_real<std::allocator<AiProcess_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
