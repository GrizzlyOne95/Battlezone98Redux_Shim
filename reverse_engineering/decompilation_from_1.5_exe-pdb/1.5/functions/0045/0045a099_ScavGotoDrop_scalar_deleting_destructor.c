/*
 * Entry: 0045a099
 * Name: ScavGotoDrop::`scalar_deleting_destructor'
 * Namespace: ScavGotoDrop
 * Signature: void * `scalar_deleting_destructor'(ScavGotoDrop * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScavGotoDrop::_scalar_deleting_destructor_(ScavGotoDrop *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
