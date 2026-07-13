/*
 * Entry: 0046ae11
 * Name: CircleTask::DoState
 * Namespace: CircleTask
 * Signature: void DoState(CircleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CircleTask::DoState(CircleTask *this)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0x3e800000;
  *(undefined4 *)(iVar1 + 0xd0) = 0x3e800000;
  *(undefined4 *)(iVar1 + 0xcc) = 0;
  return;
}
