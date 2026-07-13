/*
 * Entry: 00411a1e
 * Name: std::_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_>::~_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_>(_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_>::
~_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_>
          (_Container_base_aux_alloc_real<std::allocator<FollowerInfo>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
