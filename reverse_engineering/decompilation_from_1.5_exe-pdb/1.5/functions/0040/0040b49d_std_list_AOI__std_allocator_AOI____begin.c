/*
 * Entry: 0040b49d
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::begin
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>
 * Signature: _Iterator<1> begin(list<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::begin(list<AOI_*,std::allocator<AOI_*>_> *this)

{
  undefined4 extraout_EDX;
  _Iterator<1> _Var1;
  _Const_iterator<1> *in_stack_00000004;
  
  _Const_iterator<1>::_Const_iterator<1>(in_stack_00000004,this->_Myhead->_Next,this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
