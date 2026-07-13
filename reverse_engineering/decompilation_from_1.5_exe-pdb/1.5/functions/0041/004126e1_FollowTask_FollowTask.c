/*
 * Entry: 004126e1
 * Name: FollowTask::FollowTask
 * Namespace: FollowTask
 * Signature: FollowTask * FollowTask(FollowTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FollowTask * __thiscall FollowTask::FollowTask(FollowTask *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
