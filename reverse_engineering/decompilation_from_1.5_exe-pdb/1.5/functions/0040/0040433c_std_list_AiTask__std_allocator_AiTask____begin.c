/*
 * Entry: 0040433c
 * Name: std::list<AiTask_*,std::allocator<AiTask_*>_>::begin
 * Namespace: std::list<AiTask_*,std::allocator<AiTask_*>_>
 * Signature: _Iterator<1> begin(list<AiTask_*,std::allocator<AiTask_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<AiTask_*,std::allocator<AiTask_*>_>::begin(list<AiTask_*,std::allocator<AiTask_*>_> *this)

{
  undefined4 extraout_EDX;
  _Iterator<1> _Var1;
  _Const_iterator<1> *in_stack_00000004;
  
  _Const_iterator<1>::_Const_iterator<1>(in_stack_00000004,this->_Myhead->_Next,this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
