/*
 * Entry: 00414c21
 * Name: GoNearAndSit::`scalar_deleting_destructor'
 * Namespace: GoNearAndSit
 * Signature: void * `scalar_deleting_destructor'(GoNearAndSit * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GoNearAndSit::_scalar_deleting_destructor_(GoNearAndSit *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
