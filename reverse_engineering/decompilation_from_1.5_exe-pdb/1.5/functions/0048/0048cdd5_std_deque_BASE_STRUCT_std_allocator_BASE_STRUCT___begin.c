/*
 * Entry: 0048cdd5
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::begin
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> begin(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::begin
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  undefined4 extraout_EDX;
  _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> _Var1;
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *in_stack_00000004;
  
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
            (in_stack_00000004,this->_Myoff,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
