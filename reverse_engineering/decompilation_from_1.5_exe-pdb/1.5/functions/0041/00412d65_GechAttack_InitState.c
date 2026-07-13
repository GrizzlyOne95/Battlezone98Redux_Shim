/*
 * Entry: 00412d65
 * Name: GechAttack::InitState
 * Namespace: GechAttack
 * Signature: void InitState(GechAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechAttack::InitState(GechAttack *this)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
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
  }
  return;
}
