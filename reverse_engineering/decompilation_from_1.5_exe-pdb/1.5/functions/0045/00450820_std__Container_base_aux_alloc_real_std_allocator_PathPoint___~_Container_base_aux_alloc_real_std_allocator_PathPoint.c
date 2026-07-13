/*
 * Entry: 00450820
 * Name: std::_Container_base_aux_alloc_real<std::allocator<PathPoint>_>::~_Container_base_aux_alloc_real<std::allocator<PathPoint>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<PathPoint>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<PathPoint>_>(_Container_base_aux_alloc_real<std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<PathPoint>_>::
~_Container_base_aux_alloc_real<std::allocator<PathPoint>_>
          (_Container_base_aux_alloc_real<std::allocator<PathPoint>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
