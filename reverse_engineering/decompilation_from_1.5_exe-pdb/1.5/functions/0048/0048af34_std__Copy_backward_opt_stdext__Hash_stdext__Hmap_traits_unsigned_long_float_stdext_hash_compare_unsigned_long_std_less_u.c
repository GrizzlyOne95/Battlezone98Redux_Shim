/*
 * Entry: 0048af34
 * Name: std::_Copy_backward_opt<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position_*,std::forward_iterator_tag>
 * Namespace: std
 * Signature: _List_position * _Copy_backward_opt<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position_*,std::forward_iterator_tag>(_List_position * param_1, _List_position * param_2, _List_position * param_3, forward_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_List_position * __cdecl
std::
_Copy_backward_opt<stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position_*,stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_List_position_*,std::forward_iterator_tag>
          (_List_position *param_1,_List_position *param_2,_List_position *param_3,
          forward_iterator_tag param_4,_Nonscalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  while (param_1 != param_2) {
    *(undefined4 *)&param_3[-1]._Mypos = *(undefined4 *)&param_2[-1]._Mypos;
    *(undefined4 *)&param_3[-1]._Mypos.field_0x4 = *(undefined4 *)&param_2[-1]._Mypos.field_0x4;
    param_2 = param_2 + -1;
    param_3 = param_3 + -1;
  }
  return param_3;
}
