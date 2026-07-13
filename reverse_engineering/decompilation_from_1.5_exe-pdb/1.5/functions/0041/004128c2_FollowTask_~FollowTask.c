/*
 * Entry: 004128c2
 * Name: FollowTask::~FollowTask
 * Namespace: FollowTask
 * Signature: void ~FollowTask(FollowTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowTask::~FollowTask(FollowTask *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  if (*(FollowGroup **)&this->field_0x120 != (FollowGroup *)0x0) {
    FollowGroup::Leave(*(FollowGroup **)&this->field_0x120,*(GameObject **)&this->field_0x14);
  }
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
