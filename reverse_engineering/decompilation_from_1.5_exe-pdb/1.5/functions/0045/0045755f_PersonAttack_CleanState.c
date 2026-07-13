/*
 * Entry: 0045755f
 * Name: PersonAttack::CleanState
 * Namespace: PersonAttack
 * Signature: void CleanState(PersonAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonAttack::CleanState(PersonAttack *this)

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
