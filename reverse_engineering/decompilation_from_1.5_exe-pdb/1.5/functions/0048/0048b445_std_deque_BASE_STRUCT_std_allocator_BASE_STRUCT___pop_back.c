/*
 * Entry: 0048b445
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::pop_back
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: void pop_back(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::pop_back
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  uint uVar1;
  
  if ((this->_Mysize != 0) && (uVar1 = this->_Mysize - 1, this->_Mysize = uVar1, uVar1 == 0)) {
    this->_Myoff = 0;
  }
  return;
}
