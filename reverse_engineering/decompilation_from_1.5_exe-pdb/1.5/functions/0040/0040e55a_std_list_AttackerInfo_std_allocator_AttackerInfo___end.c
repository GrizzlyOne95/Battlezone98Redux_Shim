/*
 * Entry: 0040e55a
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::end
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: _Iterator<1> end(list<AttackerInfo,std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::end
          (list<AttackerInfo,std::allocator<AttackerInfo>_> *this)

{
  undefined4 extraout_EDX;
  _Iterator<1> _Var1;
  _Const_iterator<1> *in_stack_00000004;
  
  _Const_iterator<1>::_Const_iterator<1>(in_stack_00000004,this->_Myhead,this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
