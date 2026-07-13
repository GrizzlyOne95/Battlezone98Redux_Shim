/*
 * Entry: 004b0e16
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::end
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Signature: _Iterator<1> end(list<RtimeClass_*,std::allocator<RtimeClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::end
          (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *this)

{
  undefined4 extraout_EDX;
  _Iterator<1> _Var1;
  _Const_iterator<1> *in_stack_00000004;
  
  _Const_iterator<1>::_Const_iterator<1>(in_stack_00000004,this->_Myhead,this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
