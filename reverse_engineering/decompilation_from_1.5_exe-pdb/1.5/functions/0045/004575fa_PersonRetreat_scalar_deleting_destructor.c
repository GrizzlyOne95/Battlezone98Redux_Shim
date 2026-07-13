/*
 * Entry: 004575fa
 * Name: PersonRetreat::`scalar_deleting_destructor'
 * Namespace: PersonRetreat
 * Signature: void * `scalar_deleting_destructor'(PersonRetreat * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonRetreat::_scalar_deleting_destructor_(PersonRetreat *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
