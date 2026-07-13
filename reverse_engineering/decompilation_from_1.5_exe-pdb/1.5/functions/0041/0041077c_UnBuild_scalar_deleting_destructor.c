/*
 * Entry: 0041077c
 * Name: UnBuild::`scalar_deleting_destructor'
 * Namespace: UnBuild
 * Signature: void * `scalar_deleting_destructor'(UnBuild * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall UnBuild::_scalar_deleting_destructor_(UnBuild *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
