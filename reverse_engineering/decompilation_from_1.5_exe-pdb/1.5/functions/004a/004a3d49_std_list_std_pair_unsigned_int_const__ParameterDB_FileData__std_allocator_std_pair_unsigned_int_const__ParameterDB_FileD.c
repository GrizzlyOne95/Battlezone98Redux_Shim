/*
 * Entry: 004a3d49
 * Name: std::list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::splice
 * Namespace: std::list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
 * Signature: void splice(list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_> * this, _Const_iterator<1> param_1, list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_> * param_2, _Const_iterator<1> param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
::splice(list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
         *this,_Const_iterator<1> param_1,
        list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
        *param_2,_Const_iterator<1> param_3)

{
  _Const_iterator<1> _Var1;
  _Const_iterator<1> _Var2;
  _Const_iterator<1> _Var3;
  bool bVar4;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,param_2->_Myhead,param_2);
  bVar4 = _Const_iterator<1>::operator==(&param_3,&local_c);
  if (bVar4) {
    return;
  }
  local_c._padding_ = param_3._padding_;
  local_c._Ptr = param_3._Ptr;
  _Const_iterator<1>::operator++(&local_c);
  if (this == param_2) {
    bVar4 = _Const_iterator<1>::operator==(&param_1,&param_3);
    if (bVar4) {
      return;
    }
    bVar4 = _Const_iterator<1>::operator==(&param_1,&local_c);
    if (bVar4) {
      return;
    }
  }
  _Var1._Ptr = param_1._Ptr;
  _Var1._padding_ = param_1._padding_;
  _Var2._Ptr = param_3._Ptr;
  _Var2._padding_ = param_3._padding_;
  _Var3._Ptr = local_c._Ptr;
  _Var3._padding_ = local_c._padding_;
  _Splice(this,_Var1,param_2,_Var2,_Var3,1,false);
  return;
}
