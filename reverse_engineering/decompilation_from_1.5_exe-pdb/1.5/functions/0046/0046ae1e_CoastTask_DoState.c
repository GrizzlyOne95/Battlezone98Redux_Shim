/*
 * Entry: 0046ae1e
 * Name: CoastTask::DoState
 * Namespace: CoastTask
 * Signature: void DoState(CoastTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CoastTask::DoState(CoastTask *this)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xcc) = 0;
  return;
}
