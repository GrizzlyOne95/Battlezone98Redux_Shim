/*
 * Entry: 0040bd4d
 * Name: APCAttack::CleanState
 * Namespace: APCAttack
 * Signature: void CleanState(APCAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCAttack::CleanState(APCAttack *this)

{
  int iVar1;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 2) {
    UnitTask::CleanGoto((UnitTask *)this);
    return;
  }
  if (iVar1 != 3) {
    if (iVar1 == 5) {
                    /* WARNING: Could not recover jumptable at 0x0040bd60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(**(int **)&this->field_0x14 + 0x60))();
      return;
    }
    return;
  }
  UnitTask::CleanStuck((UnitTask *)this);
  return;
}
