/*
 * Entry: 0046f4b4
 * Name: SitSpinTask::DoState
 * Namespace: SitSpinTask
 * Signature: void DoState(SitSpinTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SitSpinTask::DoState(SitSpinTask *this)

{
  int iVar1;
  
  UnitTask::DoSit((UnitTask *)this);
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0x3f000000;
  return;
}
