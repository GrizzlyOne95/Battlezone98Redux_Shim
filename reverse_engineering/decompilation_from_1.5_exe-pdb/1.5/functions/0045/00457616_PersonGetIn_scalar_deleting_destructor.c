/*
 * Entry: 00457616
 * Name: PersonGetIn::`scalar_deleting_destructor'
 * Namespace: PersonGetIn
 * Signature: void * `scalar_deleting_destructor'(PersonGetIn * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonGetIn::_scalar_deleting_destructor_(PersonGetIn *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
