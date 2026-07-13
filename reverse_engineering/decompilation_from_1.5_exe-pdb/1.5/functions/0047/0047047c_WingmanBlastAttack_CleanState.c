/*
 * Entry: 0047047c
 * Name: WingmanBlastAttack::CleanState
 * Namespace: WingmanBlastAttack
 * Signature: void CleanState(WingmanBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanBlastAttack::CleanState(WingmanBlastAttack *this)

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
