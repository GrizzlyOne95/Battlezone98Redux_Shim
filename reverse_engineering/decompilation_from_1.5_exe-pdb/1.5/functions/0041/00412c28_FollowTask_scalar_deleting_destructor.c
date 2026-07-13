/*
 * Entry: 00412c28
 * Name: FollowTask::`scalar_deleting_destructor'
 * Namespace: FollowTask
 * Signature: void * `scalar_deleting_destructor'(FollowTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FollowTask::_scalar_deleting_destructor_(FollowTask *this,uint param_1)

{
  ~FollowTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
