/*
 * Entry: 0048bea3
 * Name: std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Namespace: std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Signature: _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>(_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * this, uint param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * __thiscall
std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::
_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
          (_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *this,uint param_1,
          _Container_base_aux *param_2)

{
  this->_padding_ = 0;
  if (((param_2 == (_Container_base_aux *)0x0) || (param_1 < param_2[6]._Myownedaux)) ||
     ((uint)((int)&(param_2[6]._Myownedaux)->_Mycontainer +
            (int)&(param_2[7]._Myownedaux)->_Mycontainer) < param_1)) {
    _invalid_parameter_noinfo();
  }
  this->_padding_ = (int)param_2->_Myownedaux;
  this->_Myoff = param_1;
  return this;
}
