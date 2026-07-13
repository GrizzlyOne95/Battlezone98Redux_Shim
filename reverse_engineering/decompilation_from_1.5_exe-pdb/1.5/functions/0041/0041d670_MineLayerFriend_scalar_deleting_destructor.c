/*
 * Entry: 0041d670
 * Name: MineLayerFriend::`scalar_deleting_destructor'
 * Namespace: MineLayerFriend
 * Signature: void * `scalar_deleting_destructor'(MineLayerFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MineLayerFriend::_scalar_deleting_destructor_(MineLayerFriend *this,uint param_1)

{
  MineLayerProcess::~MineLayerProcess((MineLayerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
