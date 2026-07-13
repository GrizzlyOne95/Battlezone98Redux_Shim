/*
 * Entry: 004132a7
 * Name: GotoGeyser::`scalar_deleting_destructor'
 * Namespace: GotoGeyser
 * Signature: void * `scalar_deleting_destructor'(GotoGeyser * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GotoGeyser::_scalar_deleting_destructor_(GotoGeyser *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
