/*
 * Entry: 00469064
 * Name: UnitProcess::CleanGoto
 * Namespace: UnitProcess
 * Signature: void CleanGoto(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanGoto(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
