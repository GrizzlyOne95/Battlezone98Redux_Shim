/*
 * Entry: 004a1b84
 * Name: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::begin
 * Namespace: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
 * Signature: _Const_iterator<1> begin(list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<1> __thiscall
std::
list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
::begin(list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
        *this)

{
  _Node *extraout_EDX;
  _Const_iterator<1> _Var1;
  _Const_iterator<1> *in_stack_00000004;
  
  _Const_iterator<1>::_Const_iterator<1>(in_stack_00000004,this->_Myhead->_Next,this);
  _Var1._Ptr = extraout_EDX;
  _Var1._padding_ = (int)in_stack_00000004;
  return _Var1;
}
