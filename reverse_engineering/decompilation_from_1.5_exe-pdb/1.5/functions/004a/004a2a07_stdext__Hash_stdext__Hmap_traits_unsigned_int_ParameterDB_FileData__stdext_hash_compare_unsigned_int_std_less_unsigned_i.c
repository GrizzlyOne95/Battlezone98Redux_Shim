/*
 * Entry: 004a2a07
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position::_List_position
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>::_List_position
 * Signature: _List_position * _List_position(_List_position * this, _Iterator<1> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_List_position * __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
::_List_position::_List_position(_List_position *this,_Iterator<1> param_1)

{
  undefined4 *puVar1;
  
  if (param_1._0_4_ == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1 = *(undefined4 **)param_1._0_4_;
  }
  *(undefined4 *)&this->_Mypos = 0;
  *(undefined4 *)&(this->_Mypos).field_0x4 = param_1._4_4_;
  *(undefined4 *)&this->_Mypos = *puVar1;
  return this;
}
