/*
 * Entry: 004a168f
 * Name: std::_Copy_backward_opt<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*>
 * Namespace: std
 * Signature: _List_position * _Copy_backward_opt<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*>(_List_position * param_1, _List_position * param_2, _List_position * param_3, random_access_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_List_position * __cdecl
std::
_Copy_backward_opt<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*>
          (_List_position *param_1,_List_position *param_2,_List_position *param_3,
          random_access_iterator_tag param_4,_Nonscalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  _Copy_backward_opt<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position_*,std::forward_iterator_tag>
            (param_1,param_2,param_3,SUB41(param_1,0),(_Nonscalar_ptr_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return param_3 + -((int)param_2 - (int)param_1 >> 3);
}
