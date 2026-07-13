/*
 * Entry: 004630e4
 * Name: SoldierAttack::CleanState
 * Namespace: SoldierAttack
 * Signature: void CleanState(SoldierAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierAttack::CleanState(SoldierAttack *this)

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
