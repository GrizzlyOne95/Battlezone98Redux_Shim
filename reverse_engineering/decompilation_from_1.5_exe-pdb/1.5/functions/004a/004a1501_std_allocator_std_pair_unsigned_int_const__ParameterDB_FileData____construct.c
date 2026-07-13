/*
 * Entry: 004a1501
 * Name: std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>::construct
 * Namespace: std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>
 * Signature: void construct(allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_> * this, pair<unsigned_int_const_,ParameterDB::FileData_*> * param_1, pair<unsigned_int_const_,ParameterDB::FileData_*> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>::construct
          (allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_> *this,
          pair<unsigned_int_const_,ParameterDB::FileData_*> *param_1,
          pair<unsigned_int_const_,ParameterDB::FileData_*> *param_2)

{
  _Construct<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>
            (param_1,param_2);
  return;
}
