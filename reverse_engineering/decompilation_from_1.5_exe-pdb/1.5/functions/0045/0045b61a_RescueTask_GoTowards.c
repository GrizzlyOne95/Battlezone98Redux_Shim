/*
 * Entry: 0045b61a
 * Name: RescueTask::GoTowards
 * Namespace: RescueTask
 * Signature: void GoTowards(RescueTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RescueTask::GoTowards(RescueTask *this)

{
  int iVar1;
  
  UnitTask::GoTowards((UnitTask *)this);
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  if (*(float *)(iVar1 + 0xd0) == 1.0) {
    *(undefined4 *)(iVar1 + 0xd4) = 1;
    return;
  }
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  return;
}
