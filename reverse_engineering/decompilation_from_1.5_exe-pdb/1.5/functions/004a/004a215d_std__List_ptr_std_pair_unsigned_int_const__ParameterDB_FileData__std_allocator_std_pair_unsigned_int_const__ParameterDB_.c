/*
 * Entry: 004a215d
 * Name: std::_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::~_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
 * Namespace: std::_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
 * Signature: void ~_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>(_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
::
~_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
          (_List_ptr<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
           *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
