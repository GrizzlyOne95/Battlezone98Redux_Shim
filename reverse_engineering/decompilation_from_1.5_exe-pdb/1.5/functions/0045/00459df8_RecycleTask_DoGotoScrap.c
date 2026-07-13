/*
 * Entry: 00459df8
 * Name: RecycleTask::DoGotoScrap
 * Namespace: RecycleTask
 * Signature: void DoGotoScrap(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::DoGotoScrap(RecycleTask *this)

{
  char cVar1;
  
  if (this->subtask != (AiTask *)0x0) {
    cVar1 = (**(code **)(this->subtask->_padding_ + 0x18))();
    if (cVar1 == '\0') {
                    /* WARNING: Could not recover jumptable at 0x00459e2e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(this->subtask->_padding_ + 0x1c))();
      return;
    }
    this->nextState = (uint)(this->me[1]._padding_ <= this->me[1]._padding_) * 2 + 1;
  }
  return;
}
