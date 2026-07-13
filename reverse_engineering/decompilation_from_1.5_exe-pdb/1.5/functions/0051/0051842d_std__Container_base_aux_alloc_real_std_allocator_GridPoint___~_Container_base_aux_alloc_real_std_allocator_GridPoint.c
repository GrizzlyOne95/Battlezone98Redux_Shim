/*
 * Entry: 0051842d
 * Name: std::_Container_base_aux_alloc_real<std::allocator<GridPoint>_>::~_Container_base_aux_alloc_real<std::allocator<GridPoint>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<GridPoint>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<GridPoint>_>(_Container_base_aux_alloc_real<std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<GridPoint>_>::
~_Container_base_aux_alloc_real<std::allocator<GridPoint>_>
          (_Container_base_aux_alloc_real<std::allocator<GridPoint>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
