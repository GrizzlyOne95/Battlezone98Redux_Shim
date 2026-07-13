/*
 * Entry: 0048d00d
 * Name: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::insert
 * Namespace: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
 * Signature: _Iterator<1> insert(list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_> * this, _Const_iterator<1> param_1, pair<unsigned_long_const_,float> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::
list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
::insert(list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
         *this,_Const_iterator<1> param_1,pair<unsigned_long_const_,float> *param_2)

{
  _Const_iterator<1> _Var1;
  _Const_iterator<1> *p_Var2;
  undefined4 extraout_EDX;
  _Iterator<1> _Var3;
  pair<unsigned_long_const_,float> *in_stack_00000010;
  
  _Var1._Ptr = (_Node *)param_2;
  _Var1._padding_ = (int)param_1._Ptr;
  _Insert(this,_Var1,in_stack_00000010);
  p_Var2 = _Const_iterator<1>::operator--((_Const_iterator<1> *)&param_1._Ptr);
  _Const_iterator<1>::_Const_iterator<1>((_Const_iterator<1> *)param_1._padding_,p_Var2->_Ptr,this);
  _Var3._4_4_ = extraout_EDX;
  _Var3._0_4_ = param_1._padding_;
  return _Var3;
}
