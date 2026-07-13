/*
 * Entry: 004705b0
 * Name: RocketTankAttack::CleanState
 * Namespace: RocketTankAttack
 * Signature: void CleanState(RocketTankAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankAttack::CleanState(RocketTankAttack *this)

{
  int iVar1;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 2) {
    UnitTask::CleanGoto((UnitTask *)this);
    return;
  }
  if (iVar1 != 3) {
    if (iVar1 == 5) {
      UnitTask::CleanSpecial((UnitTask *)this);
      return;
    }
    return;
  }
  UnitTask::CleanStuck((UnitTask *)this);
  return;
}
