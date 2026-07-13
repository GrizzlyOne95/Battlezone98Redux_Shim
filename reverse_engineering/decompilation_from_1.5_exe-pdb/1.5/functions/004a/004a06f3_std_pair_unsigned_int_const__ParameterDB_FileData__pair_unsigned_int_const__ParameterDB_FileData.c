/*
 * Entry: 004a06f3
 * Name: std::pair<unsigned_int_const_,ParameterDB::FileData_*>::pair<unsigned_int_const_,ParameterDB::FileData_*>
 * Namespace: std::pair<unsigned_int_const_,ParameterDB::FileData_*>
 * Signature: pair<unsigned_int_const_,ParameterDB::FileData_*> * pair<unsigned_int_const_,ParameterDB::FileData_*>(pair<unsigned_int_const_,ParameterDB::FileData_*> * this, uint * param_1, FileData * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_int_const_,ParameterDB::FileData_*> * __thiscall
std::pair<unsigned_int_const_,ParameterDB::FileData_*>::
pair<unsigned_int_const_,ParameterDB::FileData_*>
          (pair<unsigned_int_const_,ParameterDB::FileData_*> *this,uint *param_1,FileData **param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
