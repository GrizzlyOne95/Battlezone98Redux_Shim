/*
 * Entry: 00414be9
 * Name: GoPoints::`scalar_deleting_destructor'
 * Namespace: GoPoints
 * Signature: void * `scalar_deleting_destructor'(GoPoints * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GoPoints::_scalar_deleting_destructor_(GoPoints *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
