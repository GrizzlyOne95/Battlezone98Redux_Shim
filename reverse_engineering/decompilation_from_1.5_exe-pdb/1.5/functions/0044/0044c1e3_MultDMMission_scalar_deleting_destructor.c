/*
 * Entry: 0044c1e3
 * Name: MultDMMission::`scalar_deleting_destructor'
 * Namespace: MultDMMission
 * Signature: void * `scalar_deleting_destructor'(MultDMMission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MultDMMission::_scalar_deleting_destructor_(MultDMMission *this,uint param_1)

{
  ~MultDMMission(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
