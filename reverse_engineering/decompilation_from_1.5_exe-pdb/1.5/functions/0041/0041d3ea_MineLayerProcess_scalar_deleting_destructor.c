/*
 * Entry: 0041d3ea
 * Name: MineLayerProcess::`scalar_deleting_destructor'
 * Namespace: MineLayerProcess
 * Signature: void * `scalar_deleting_destructor'(MineLayerProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
MineLayerProcess::_scalar_deleting_destructor_(MineLayerProcess *this,uint param_1)

{
  ~MineLayerProcess(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
