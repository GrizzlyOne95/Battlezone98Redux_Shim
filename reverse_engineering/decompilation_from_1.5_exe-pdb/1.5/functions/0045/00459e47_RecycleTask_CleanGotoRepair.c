/*
 * Entry: 00459e47
 * Name: RecycleTask::CleanGotoRepair
 * Namespace: RecycleTask
 * Signature: void CleanGotoRepair(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::CleanGotoRepair(RecycleTask *this)

{
  if (this->subtask != (AiTask *)0x0) {
    (**(code **)this->subtask->_padding_)(1);
    this->subtask = (AiTask *)0x0;
  }
  return;
}
