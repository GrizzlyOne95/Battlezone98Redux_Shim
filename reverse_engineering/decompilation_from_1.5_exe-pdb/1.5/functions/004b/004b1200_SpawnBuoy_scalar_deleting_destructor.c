/*
 * Entry: 004b1200
 * Name: SpawnBuoy::`scalar_deleting_destructor'
 * Namespace: SpawnBuoy
 * Signature: void * `scalar_deleting_destructor'(SpawnBuoy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SpawnBuoy::_scalar_deleting_destructor_(SpawnBuoy *this,uint param_1)

{
  ~SpawnBuoy(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
