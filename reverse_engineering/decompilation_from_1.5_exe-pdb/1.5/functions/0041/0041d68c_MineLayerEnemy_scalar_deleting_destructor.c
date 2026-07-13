/*
 * Entry: 0041d68c
 * Name: MineLayerEnemy::`scalar_deleting_destructor'
 * Namespace: MineLayerEnemy
 * Signature: void * `scalar_deleting_destructor'(MineLayerEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MineLayerEnemy::_scalar_deleting_destructor_(MineLayerEnemy *this,uint param_1)

{
  MineLayerProcess::~MineLayerProcess((MineLayerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
