/*
 * Entry: 0045b4f4
 * Name: RecycleTask::InitState
 * Namespace: RecycleTask
 * Signature: void InitState(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::InitState(RecycleTask *this)

{
  int iVar1;
  
  iVar1 = this->curState;
  if (iVar1 == 0) {
    this->curState = 1;
  }
  else if (iVar1 != 1) {
    if (iVar1 == 2) {
      InitGotoScrap(this);
      return;
    }
    if (iVar1 == 3) {
      InitGotoRecycler(this);
      return;
    }
    if (iVar1 == 4) {
      InitGotoRepair(this);
      return;
    }
    if (iVar1 != 5) {
      if (iVar1 == 7) {
        this->stuckState = 0;
      }
      return;
    }
    InitWait(this);
    return;
  }
  CleanStuck(this);
  InitLookingForScrap(this);
  return;
}
