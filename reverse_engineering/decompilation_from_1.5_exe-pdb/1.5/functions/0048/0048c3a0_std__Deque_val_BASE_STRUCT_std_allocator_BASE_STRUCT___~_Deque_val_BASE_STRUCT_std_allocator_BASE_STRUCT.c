/*
 * Entry: 0048c3a0
 * Name: std::_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::~_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Namespace: std::_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: void ~_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>(_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::
~_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
          (_Deque_val<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
