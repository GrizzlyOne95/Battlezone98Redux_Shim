/*
 * Entry: 0045a32a
 * Name: RecycleTask::CleanState
 * Namespace: RecycleTask
 * Signature: void CleanState(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::CleanState(RecycleTask *this)

{
  int iVar1;
  
  iVar1 = this->curState;
  if (iVar1 != 1) {
    if (iVar1 == 2) {
      CleanGotoScrap(this);
      return;
    }
    if (iVar1 == 3) {
      CleanGotoRecycler(this);
      return;
    }
    if (iVar1 == 4) {
      CleanGotoRepair(this);
      return;
    }
    if ((iVar1 != 5) && (iVar1 == 7)) {
      CleanStuck(this);
      return;
    }
  }
  return;
}
