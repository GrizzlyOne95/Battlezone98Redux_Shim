/*
 * Entry: 004a0d54
 * Name: std::_Construct<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>
 * Namespace: std
 * Signature: void _Construct<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>(pair<unsigned_int_const_,ParameterDB::FileData_*> * param_1, pair<unsigned_int_const_,ParameterDB::FileData_*> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Construct<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>
          (pair<unsigned_int_const_,ParameterDB::FileData_*> *param_1,
          pair<unsigned_int_const_,ParameterDB::FileData_*> *param_2)

{
  if (param_1 != (pair<unsigned_int_const_,ParameterDB::FileData_*> *)0x0) {
    param_1->first = param_2->first;
    param_1->second = param_2->second;
  }
  return;
}
