/*
 * Entry: 0048a331
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::empty
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: bool empty(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::empty
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  return this->_Mysize == 0;
}
