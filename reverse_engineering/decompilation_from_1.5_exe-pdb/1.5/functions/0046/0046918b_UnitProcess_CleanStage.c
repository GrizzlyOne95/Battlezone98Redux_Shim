/*
 * Entry: 0046918b
 * Name: UnitProcess::CleanStage
 * Namespace: UnitProcess
 * Signature: void CleanStage(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanStage(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
