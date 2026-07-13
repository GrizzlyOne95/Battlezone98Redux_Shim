/*
 * Entry: 004a07a1
 * Name: std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position>::deallocate
 * Namespace: std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position>
 * Signature: void deallocate(allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position> * this, _List_position * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position>
::deallocate(allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position>
             *this,_List_position *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
