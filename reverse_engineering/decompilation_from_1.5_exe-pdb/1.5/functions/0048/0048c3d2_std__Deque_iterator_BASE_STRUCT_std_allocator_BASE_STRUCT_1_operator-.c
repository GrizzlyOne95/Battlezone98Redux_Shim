/*
 * Entry: 0048c3d2
 * Name: std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator-
 * Namespace: std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Signature: _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> operator-(_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> __thiscall
std::_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator-
          (_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *this,int param_1)

{
  undefined4 extraout_EDX;
  _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> _Var1;
  int in_stack_00000008;
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> local_c;
  
  local_c._padding_ = *(int *)this;
  local_c._Myoff = *(uint *)&this->field_0x4;
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator+=
            (&local_c,-in_stack_00000008);
  *(int *)param_1 = local_c._padding_;
  *(uint *)(param_1 + 4) = local_c._Myoff;
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1;
  return _Var1;
}
