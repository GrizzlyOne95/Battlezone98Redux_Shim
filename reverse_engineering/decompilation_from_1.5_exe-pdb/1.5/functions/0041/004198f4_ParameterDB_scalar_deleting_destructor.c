/*
 * Entry: 004198f4
 * Name: ParameterDB::`scalar_deleting_destructor'
 * Namespace: ParameterDB
 * Signature: void * `scalar_deleting_destructor'(ParameterDB * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ParameterDB::_scalar_deleting_destructor_(ParameterDB *this,uint param_1)

{
  ~ParameterDB(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
