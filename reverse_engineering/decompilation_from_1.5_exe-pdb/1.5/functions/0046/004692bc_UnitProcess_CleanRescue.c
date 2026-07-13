/*
 * Entry: 004692bc
 * Name: UnitProcess::CleanRescue
 * Namespace: UnitProcess
 * Signature: void CleanRescue(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanRescue(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
