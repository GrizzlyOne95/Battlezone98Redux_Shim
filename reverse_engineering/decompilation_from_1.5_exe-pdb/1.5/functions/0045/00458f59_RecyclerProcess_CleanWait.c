/*
 * Entry: 00458f59
 * Name: RecyclerProcess::CleanWait
 * Namespace: RecyclerProcess
 * Signature: void CleanWait(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::CleanWait(RecyclerProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
