/*
 * Entry: 0048b42a
 * Name: std::_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_>::~_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_>(_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_>::
~_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_>
          (_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_long_const_,float>_>_>
           *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
