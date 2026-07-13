/*
 * Entry: 00414c05
 * Name: GoGet::`scalar_deleting_destructor'
 * Namespace: GoGet
 * Signature: void * `scalar_deleting_destructor'(GoGet * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GoGet::_scalar_deleting_destructor_(GoGet *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
