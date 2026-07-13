/*
 * Entry: 004a1fc8
 * Name: std::fill<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>
 * Namespace: std
 * Signature: void fill<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>(_List_position * param_1, _List_position * param_2, _List_position * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
fill<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>
          (_List_position *param_1,_List_position *param_2,_List_position *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *(undefined4 *)&param_1->_Mypos = *(undefined4 *)&param_3->_Mypos;
    *(undefined4 *)&(param_1->_Mypos).field_0x4 = *(undefined4 *)&(param_3->_Mypos).field_0x4;
  }
  return;
}
