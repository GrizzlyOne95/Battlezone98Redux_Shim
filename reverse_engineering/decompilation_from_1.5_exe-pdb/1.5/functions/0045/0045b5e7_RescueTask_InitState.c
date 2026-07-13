/*
 * Entry: 0045b5e7
 * Name: RescueTask::InitState
 * Namespace: RescueTask
 * Signature: void InitState(RescueTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RescueTask::InitState(RescueTask *this)

{
  int iVar1;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    *(undefined4 *)&this->field_0x10 = 4;
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
