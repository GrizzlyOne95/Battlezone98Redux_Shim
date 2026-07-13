/*
 * Entry: 0048cba1
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::~deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: void ~deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::
~deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
