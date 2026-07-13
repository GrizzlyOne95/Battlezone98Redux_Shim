/*
 * Entry: 0045bac7
 * Name: SAVAttackPersonTask::CleanState
 * Namespace: SAVAttackPersonTask
 * Signature: void CleanState(SAVAttackPersonTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackPersonTask::CleanState(SAVAttackPersonTask *this)

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
