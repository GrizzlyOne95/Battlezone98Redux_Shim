/*
 * Entry: 00470455
 * Name: WingmanBlastAttack::InitState
 * Namespace: WingmanBlastAttack
 * Signature: void InitState(WingmanBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanBlastAttack::InitState(WingmanBlastAttack *this)

{
  int iVar1;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    *(undefined4 *)&this->field_0xc = 5;
  }
  else {
    if (iVar1 == 2) {
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
    if (iVar1 == 3) {
      UnitTask::InitStuck((UnitTask *)this);
      return;
    }
    if (iVar1 != 5) {
      return;
    }
  }
  UnitTask::InitSpecial((UnitTask *)this);
  return;
}
