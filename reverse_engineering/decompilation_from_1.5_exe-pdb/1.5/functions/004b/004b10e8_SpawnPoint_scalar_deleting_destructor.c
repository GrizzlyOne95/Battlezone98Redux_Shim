/*
 * Entry: 004b10e8
 * Name: SpawnPoint::`scalar_deleting_destructor'
 * Namespace: SpawnPoint
 * Signature: void * `scalar_deleting_destructor'(SpawnPoint * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SpawnPoint::_scalar_deleting_destructor_(SpawnPoint *this,uint param_1)

{
  ~SpawnPoint(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
