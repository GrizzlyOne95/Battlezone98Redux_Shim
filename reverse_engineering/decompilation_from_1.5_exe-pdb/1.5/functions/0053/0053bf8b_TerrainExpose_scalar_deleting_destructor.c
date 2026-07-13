/*
 * Entry: 0053bf8b
 * Name: TerrainExpose::`scalar_deleting_destructor'
 * Namespace: TerrainExpose
 * Signature: void * `scalar_deleting_destructor'(TerrainExpose * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TerrainExpose::_scalar_deleting_destructor_(TerrainExpose *this,uint param_1)

{
  ~TerrainExpose(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
