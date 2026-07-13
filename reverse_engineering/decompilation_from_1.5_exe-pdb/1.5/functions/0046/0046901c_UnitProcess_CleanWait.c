/*
 * Entry: 0046901c
 * Name: UnitProcess::CleanWait
 * Namespace: UnitProcess
 * Signature: void CleanWait(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanWait(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
