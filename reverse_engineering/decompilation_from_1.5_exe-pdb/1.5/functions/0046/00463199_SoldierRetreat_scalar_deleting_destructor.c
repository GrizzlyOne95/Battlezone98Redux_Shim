/*
 * Entry: 00463199
 * Name: SoldierRetreat::`scalar_deleting_destructor'
 * Namespace: SoldierRetreat
 * Signature: void * `scalar_deleting_destructor'(SoldierRetreat * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SoldierRetreat::_scalar_deleting_destructor_(SoldierRetreat *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
