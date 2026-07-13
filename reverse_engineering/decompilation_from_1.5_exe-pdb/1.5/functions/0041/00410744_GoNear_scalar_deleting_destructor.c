/*
 * Entry: 00410744
 * Name: GoNear::`scalar_deleting_destructor'
 * Namespace: GoNear
 * Signature: void * `scalar_deleting_destructor'(GoNear * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GoNear::_scalar_deleting_destructor_(GoNear *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
