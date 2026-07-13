/*
 * Entry: 00410bcc
 * Name: DefendTask::CleanState
 * Namespace: DefendTask
 * Signature: void CleanState(DefendTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DefendTask::CleanState(DefendTask *this)

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
