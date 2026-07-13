/*
 * Entry: 00459de2
 * Name: RecycleTask::CleanGotoScrap
 * Namespace: RecycleTask
 * Signature: void CleanGotoScrap(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::CleanGotoScrap(RecycleTask *this)

{
  if (this->subtask != (AiTask *)0x0) {
    (**(code **)this->subtask->_padding_)(1);
    this->subtask = (AiTask *)0x0;
  }
  return;
}
