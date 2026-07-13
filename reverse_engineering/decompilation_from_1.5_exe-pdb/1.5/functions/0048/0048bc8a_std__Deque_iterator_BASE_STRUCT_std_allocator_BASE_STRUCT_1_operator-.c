/*
 * Entry: 0048bc8a
 * Name: std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator-=
 * Namespace: std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Signature: _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * operator-=(_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * __thiscall
std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator-=
          (_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *this,int param_1)

{
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator+=
            ((_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *)this,-param_1);
  return this;
}
