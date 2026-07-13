/*
 * Entry: 004e1148
 * Name: std::_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>::~_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
 * Namespace: std::_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
 * Signature: void ~_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>(_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
::~_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
          (_Container_base_aux_alloc_real<std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
           *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
