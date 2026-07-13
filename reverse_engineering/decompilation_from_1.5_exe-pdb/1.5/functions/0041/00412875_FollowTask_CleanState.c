/*
 * Entry: 00412875
 * Name: FollowTask::CleanState
 * Namespace: FollowTask
 * Signature: void CleanState(FollowTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowTask::CleanState(FollowTask *this)

{
  if (*(int *)&this->field_0xc == 2) {
    UnitTask::CleanGoto((UnitTask *)this);
    return;
  }
  if (*(int *)&this->field_0xc == 3) {
    UnitTask::CleanStuck((UnitTask *)this);
    return;
  }
  return;
}
