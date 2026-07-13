/*
 * Entry: 00466122
 * Name: TugPickup::`scalar_deleting_destructor'
 * Namespace: TugPickup
 * Signature: void * `scalar_deleting_destructor'(TugPickup * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TugPickup::_scalar_deleting_destructor_(TugPickup *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
