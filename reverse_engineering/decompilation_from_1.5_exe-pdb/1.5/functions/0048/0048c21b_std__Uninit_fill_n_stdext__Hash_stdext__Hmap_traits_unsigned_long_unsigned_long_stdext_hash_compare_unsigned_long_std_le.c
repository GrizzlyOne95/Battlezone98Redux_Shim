/*
 * Entry: 0048c21b
 * Name: std::_Uninit_fill_n<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position_*,unsigned_int,stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position_*,unsigned_int,stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>(_List_position * param_1, uint param_2, _List_position * param_3, allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position> * param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Uninit_fill_n<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position_*,unsigned_int,stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>_>
          (_List_position *param_1,uint param_2,_List_position *param_3,
          allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>
          *param_4,_Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    _Construct<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position,stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::_List_position>
              (param_1,param_3);
    param_1 = param_1 + 1;
  }
  return;
}
