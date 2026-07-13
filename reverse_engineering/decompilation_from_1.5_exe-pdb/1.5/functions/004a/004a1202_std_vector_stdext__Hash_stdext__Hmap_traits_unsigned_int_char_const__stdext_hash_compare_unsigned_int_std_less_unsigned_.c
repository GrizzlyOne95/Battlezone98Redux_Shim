/*
 * Entry: 004a1202
 * Name: std::vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>::operator[]
 * Namespace: std::vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
 * Signature: _List_position * operator[](vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_List_position * __thiscall
std::
vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
::operator[](vector<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position,std::allocator<stdext::_Hash<stdext::_Hmap_traits<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>,0>_>::_List_position>_>
             *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 3) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
