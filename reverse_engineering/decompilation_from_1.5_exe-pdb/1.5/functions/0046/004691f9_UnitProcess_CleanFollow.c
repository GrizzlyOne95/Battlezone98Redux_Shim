/*
 * Entry: 004691f9
 * Name: UnitProcess::CleanFollow
 * Namespace: UnitProcess
 * Signature: void CleanFollow(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanFollow(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
