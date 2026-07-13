/*
 * Entry: 004a4b7b
 * Name: ParameterDB::~ParameterDB
 * Namespace: ParameterDB
 * Signature: void ~ParameterDB(ParameterDB * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ParameterDB::~ParameterDB(ParameterDB *this)

{
  FileData *this_00;
  _Const_iterator<1> _Var1;
  bool bVar2;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  this->DB_file->DB_ref = this->DB_file->DB_ref + -1;
  if (this->DB_file->DB_ref < 1) {
    local_c._Ptr = (_Node *)Hash(this->DB_file->DB_name,0x811c9dc5);
    stdext::
    _Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
    ::lower_bound((_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
                   *)&DB_open,(uint *)&local_14);
    std::
    list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>
              (&local_c,(_Node *)DB_open._28_4_,
               (list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
                *)&DB_open.field_0x8);
    bVar2 = std::
            list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
            ::_Const_iterator<1>::operator==(&local_14,&local_c);
    if (!bVar2) {
      _Var1._Ptr = (_Node *)local_14._padding_;
      _Var1._padding_ = (int)&local_14;
      stdext::
      _Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
      ::erase((_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
               *)&DB_open,_Var1);
    }
    this_00 = this->DB_file;
    if (this_00 != (FileData *)0x0) {
      FileData::~FileData(this_00);
      operator_delete(this_00);
    }
  }
  return;
}
