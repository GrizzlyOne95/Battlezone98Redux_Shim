/*
 * Entry: 004a0b82
 * Name: std::_Allocate<std::_List_nod<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::_Node>
 * Namespace: std
 * Signature: _Node * _Allocate<std::_List_nod<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::_Node>(uint param_1, _Node * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __cdecl
std::
_Allocate<std::_List_nod<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::_Node>
          (uint param_1,_Node *param_2)

{
  _Node *p_Var1;
  undefined **in_ECX;
  exception local_c;
  
  local_c._padding_ = (int)in_ECX;
  local_c._Ptr = (char *)in_ECX;
  if (param_1 == 0) {
    param_1 = 0;
  }
  else if ((uint)(0xffffffff / (ulonglong)param_1) < 0x10) {
    local_c._Ptr = (char *)0x0;
    local_c._padding_ = (int)&stdext::bad_alloc::_vftable_;
    stdext::exception::_Raise(&local_c);
  }
  p_Var1 = operator_new(param_1 << 4);
  return p_Var1;
}
