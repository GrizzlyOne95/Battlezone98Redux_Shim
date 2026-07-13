/*
 * Entry: 00412da5
 * Name: GechAttack::CleanState
 * Namespace: GechAttack
 * Signature: void CleanState(GechAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechAttack::CleanState(GechAttack *this)

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
