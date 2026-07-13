/*
 * Entry: 0045afcf
 * Name: RecycleTask::DoState
 * Namespace: RecycleTask
 * Signature: void DoState(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::DoState(RecycleTask *this)

{
  int iVar1;
  
  iVar1 = this->curState;
  if (iVar1 != 1) {
    if (iVar1 == 2) {
      DoGotoScrap(this);
      return;
    }
    if (iVar1 == 3) {
      DoGotoRecycler(this);
      return;
    }
    if (iVar1 == 4) {
      DoGotoRepair(this);
      return;
    }
    if (iVar1 == 5) {
      DoWait(this);
      return;
    }
    if (iVar1 == 7) {
      DoStuck(this);
      return;
    }
  }
  return;
}
