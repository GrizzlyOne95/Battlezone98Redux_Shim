/*
 * Entry: 0045a0b5
 * Name: ScavGotoRepair::`scalar_deleting_destructor'
 * Namespace: ScavGotoRepair
 * Signature: void * `scalar_deleting_destructor'(ScavGotoRepair * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScavGotoRepair::_scalar_deleting_destructor_(ScavGotoRepair *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
