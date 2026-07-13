/*
 * Entry: 00459e31
 * Name: RecycleTask::CleanGotoRecycler
 * Namespace: RecycleTask
 * Signature: void CleanGotoRecycler(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::CleanGotoRecycler(RecycleTask *this)

{
  if (this->subtask != (AiTask *)0x0) {
    (**(code **)this->subtask->_padding_)(1);
    this->subtask = (AiTask *)0x0;
  }
  return;
}
