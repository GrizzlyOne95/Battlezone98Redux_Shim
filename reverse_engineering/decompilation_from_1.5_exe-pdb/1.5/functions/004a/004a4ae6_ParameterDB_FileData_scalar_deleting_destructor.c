/*
 * Entry: 004a4ae6
 * Name: ParameterDB::FileData::`scalar_deleting_destructor'
 * Namespace: ParameterDB::FileData
 * Signature: void * `scalar_deleting_destructor'(FileData * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ParameterDB::FileData::_scalar_deleting_destructor_(FileData *this,uint param_1)

{
  ~FileData(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
