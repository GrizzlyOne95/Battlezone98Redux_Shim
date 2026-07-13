/*
 * Entry: 004690e6
 * Name: UnitProcess::CleanPatrol
 * Namespace: UnitProcess
 * Signature: void CleanPatrol(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanPatrol(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
