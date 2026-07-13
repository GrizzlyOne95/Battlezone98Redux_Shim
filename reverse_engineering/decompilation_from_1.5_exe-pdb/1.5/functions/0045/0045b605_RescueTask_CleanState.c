/*
 * Entry: 0045b605
 * Name: RescueTask::CleanState
 * Namespace: RescueTask
 * Signature: void CleanState(RescueTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RescueTask::CleanState(RescueTask *this)

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
