/*
 * Entry: 004a26a1
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_Get_iter_from_vec
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
 * Signature: _Iterator<1> _Get_iter_from_vec(_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_> * this, _List_position * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
::_Get_iter_from_vec
          (_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
           *this,_List_position *param_1)

{
  _Iterator<1> _Var1;
  undefined4 unaff_retaddr;
  _List_position *in_stack_00000008;
  
  _Var1 = _List_position::_Get_iter
                    (in_stack_00000008,
                     (list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
                      *)param_1);
  _Var1._0_4_ = unaff_retaddr;
  return _Var1;
}
