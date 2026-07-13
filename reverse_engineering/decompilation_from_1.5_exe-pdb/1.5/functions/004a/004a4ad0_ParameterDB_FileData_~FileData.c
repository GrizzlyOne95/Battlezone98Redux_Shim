/*
 * Entry: 004a4ad0
 * Name: ParameterDB::FileData::~FileData
 * Namespace: ParameterDB::FileData
 * Signature: void ~FileData(FileData * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ParameterDB::FileData::~FileData(FileData *this)

{
  free(this->DB_data);
  stdext::
  _Hash<stdext::_Hmap_traits<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>,0>_>
  ::
  ~_Hash<stdext::_Hmap_traits<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>,0>_>
            ((_Hash<stdext::_Hmap_traits<unsigned_int,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,stdext::hash_map<unsigned_int,char_const_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>_>_>,0>_>
              *)&this->DB_map);
  return;
}
