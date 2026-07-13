/*
 * Entry: 004a0eef
 * Name: std::_Construct<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>
 * Namespace: std
 * Signature: void _Construct<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>(_List_position * param_1, _List_position * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Construct<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>
          (_List_position *param_1,_List_position *param_2)

{
  if (param_1 != (_List_position *)0x0) {
    *(undefined4 *)&param_1->_Mypos = *(undefined4 *)&param_2->_Mypos;
    *(undefined4 *)&(param_1->_Mypos).field_0x4 = *(undefined4 *)&(param_2->_Mypos).field_0x4;
  }
  return;
}
