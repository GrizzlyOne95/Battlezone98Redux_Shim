/*
 * Entry: 004a524b
 * Name: ParameterDB::ParameterDB
 * Namespace: ParameterDB
 * Signature: ParameterDB * ParameterDB(ParameterDB * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ParameterDB * __thiscall ParameterDB::ParameterDB(ParameterDB *this,char *param_1)

{
  bool bVar1;
  pair<unsigned_int_const_,ParameterDB::FileData_*> *ppVar2;
  FileData *pFVar3;
  FileData **ppFVar4;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  uint local_8;
  
  local_8 = Hash(param_1,0x811c9dc5);
  stdext::
  _Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
  ::lower_bound((_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
                 *)&DB_open,(uint *)&local_10);
  std::
  list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
  ::_Const_iterator<1>::_Const_iterator<1>
            (&local_18,(_Node *)DB_open._28_4_,
             (list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
              *)&DB_open.field_0x8);
  bVar1 = std::
          list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
          ::_Const_iterator<1>::operator==(&local_10,&local_18);
  if (bVar1) {
    pFVar3 = operator_new(0x60);
    if (pFVar3 == (FileData *)0x0) {
      pFVar3 = (FileData *)0x0;
    }
    else {
      pFVar3 = FileData::FileData(pFVar3,param_1);
    }
    ppFVar4 = stdext::
              hash_map<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
              ::operator[](&DB_open,&local_8);
    *ppFVar4 = pFVar3;
    this->DB_file = pFVar3;
  }
  else {
    ppVar2 = std::
             list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
             ::_Const_iterator<1>::operator*(&local_10);
    pFVar3 = ppVar2->second;
    this->DB_file = pFVar3;
    pFVar3->DB_ref = pFVar3->DB_ref + 1;
  }
  return this;
}
