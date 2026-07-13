/*
 * Entry: 00469248
 * Name: UnitProcess::CleanDefend
 * Namespace: UnitProcess
 * Signature: void CleanDefend(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanDefend(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
