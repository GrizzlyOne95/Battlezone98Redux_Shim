/*
 * Entry: 00459e5d
 * Name: RecycleTask::DoGotoRepair
 * Namespace: RecycleTask
 * Signature: void DoGotoRepair(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::DoGotoRepair(RecycleTask *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(this->subtask->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    this->nextState = 1;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00459e7b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->subtask->_padding_ + 0x1c))();
  return;
}
