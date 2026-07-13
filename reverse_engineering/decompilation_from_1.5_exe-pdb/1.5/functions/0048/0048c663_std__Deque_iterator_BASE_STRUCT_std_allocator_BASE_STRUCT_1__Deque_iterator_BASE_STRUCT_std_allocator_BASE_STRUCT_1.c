/*
 * Entry: 0048c663
 * Name: std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Namespace: std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Signature: _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>(_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * this, uint param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * __thiscall
std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::
_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
          (_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *this,uint param_1,
          _Container_base_aux *param_2)

{
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
            ((_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *)this,param_1,
             param_2);
  return this;
}
