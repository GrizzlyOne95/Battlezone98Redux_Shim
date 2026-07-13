/*
 * Entry: 00537d74
 * Name: RemoteDetonator::`scalar_deleting_destructor'
 * Namespace: RemoteDetonator
 * Signature: void * `scalar_deleting_destructor'(RemoteDetonator * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RemoteDetonator::_scalar_deleting_destructor_(RemoteDetonator *this,uint param_1)

{
  ~RemoteDetonator(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
