/*
 * Entry: 004a25f2
 * Name: std::_Fill<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position_*,std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>_>
 * Namespace: std
 * Signature: void _Fill<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position_*,std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>_>(_List_position * param_1, _List_position * param_2, _Iterator<1> * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Fill<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position_*,std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Iterator<1>_>
          (_List_position *param_1,_List_position *param_2,_Iterator<1> *param_3)

{
  _List_position local_c;
  
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    stdext::
    _Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>
    ::_List_position::_List_position(&local_c,*param_3);
    *(undefined4 *)&param_1->_Mypos = local_c._Mypos._0_4_;
    *(undefined4 *)&(param_1->_Mypos).field_0x4 = local_c._Mypos._4_4_;
  }
  return;
}
