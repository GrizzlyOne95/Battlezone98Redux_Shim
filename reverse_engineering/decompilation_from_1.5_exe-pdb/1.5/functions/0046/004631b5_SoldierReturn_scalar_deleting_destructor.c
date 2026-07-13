/*
 * Entry: 004631b5
 * Name: SoldierReturn::`scalar_deleting_destructor'
 * Namespace: SoldierReturn
 * Signature: void * `scalar_deleting_destructor'(SoldierReturn * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SoldierReturn::_scalar_deleting_destructor_(SoldierReturn *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
