/*
 * Entry: 004a46fc
 * Name: ParameterDBFeature::PostRun
 * Namespace: ParameterDBFeature
 * Signature: void PostRun(ParameterDBFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ParameterDBFeature::PostRun(ParameterDBFeature *this)

{
  if (ParameterDB::DB_open._32_4_ != 0) {
    TraceWarning("%d ParameterDB entries still open\n");
  }
  stdext::
  _Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
  ::clear((_Hash<stdext::_Hmap_traits<unsigned_int,ParameterDB::FileData_*,stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>,0>_>
           *)&ParameterDB::DB_open);
  return;
}
