/*
 * Entry: 004a1859
 * Name: std::list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::_Iterator<1>::operator*
 * Namespace: std::list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>::_Iterator<1>
 * Signature: pair<unsigned_int_const_,ParameterDB::FileData_*> * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_int_const_,ParameterDB::FileData_*> * __thiscall
std::
list<std::pair<unsigned_int_const_,ParameterDB::FileData_*>,std::allocator<std::pair<unsigned_int_const_,ParameterDB::FileData_*>_>_>
::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004a0fcd;
    }
  }
  iVar2 = *piVar1;
LAB_004a0fcd:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (pair<unsigned_int_const_,ParameterDB::FileData_*> *)(*(int *)&this->field_0x4 + 8);
}
