/*
 * Entry: 0045ba8c
 * Name: SAVAttackPersonTask::InitState
 * Namespace: SAVAttackPersonTask
 * Signature: void InitState(SAVAttackPersonTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackPersonTask::InitState(SAVAttackPersonTask *this)

{
  int iVar1;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    *(undefined4 *)&this->field_0xc = 5;
  }
  else {
    if (iVar1 == 2) {
      (**(code **)(**(int **)&this->field_0x14 + 0x5c))();
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
                    /* WARNING: Could not recover jumptable at 0x0045bac4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x14 + 0x60))();
  return;
}
