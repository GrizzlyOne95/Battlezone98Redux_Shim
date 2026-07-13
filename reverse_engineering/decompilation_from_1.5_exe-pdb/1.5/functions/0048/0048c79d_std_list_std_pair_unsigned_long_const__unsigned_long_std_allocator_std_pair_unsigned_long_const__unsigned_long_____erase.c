/*
 * Entry: 0048c79d
 * Name: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::erase
 * Namespace: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
 * Signature: _Iterator<1> erase(list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_> * this, _Const_iterator<1> param_1, _Const_iterator<1> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::
list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
::erase(list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
        *this,_Const_iterator<1> param_1,_Const_iterator<1> param_2)

{
  _Const_iterator<1> _Var1;
  bool bVar2;
  undefined4 extraout_EDX;
  _Iterator<1> _Var3;
  _Node *in_stack_00000014;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead->_Next,this);
  bVar2 = _Const_iterator<1>::operator==((_Const_iterator<1> *)&param_1._Ptr,&local_c);
  if (bVar2) {
    _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
    bVar2 = _Const_iterator<1>::operator==((_Const_iterator<1> *)&param_2._Ptr,&local_c);
    if (bVar2) {
      clear(this);
      in_stack_00000014 = this->_Myhead;
      goto LAB_0048c81c;
    }
  }
  while (bVar2 = _Const_iterator<1>::operator==
                           ((_Const_iterator<1> *)&param_1._Ptr,(_Const_iterator<1> *)&param_2._Ptr)
        , !bVar2) {
    _Var1._Ptr = param_1._Ptr;
    _Var1._padding_ = (int)&local_c;
    _Var3 = erase(this,_Var1);
    param_1._Ptr = (_Node *)*_Var3._0_4_;
    param_2._padding_ = _Var3._0_4_[1];
  }
LAB_0048c81c:
  _Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)param_1._padding_,in_stack_00000014,this);
  _Var3._4_4_ = extraout_EDX;
  _Var3._0_4_ = param_1._padding_;
  return _Var3;
}
