/*
 * Entry: 0045b543
 * Name: RecycleTask::Execute
 * Namespace: RecycleTask
 * Signature: void Execute(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::Execute(RecycleTask *this)

{
  if (this->nextState != 8) {
    CleanState(this);
    this->curState = this->nextState;
    this->nextState = 8;
    InitState(this);
    if (this->nextState != 8) {
      return;
    }
  }
  DoState(this);
  return;
}
