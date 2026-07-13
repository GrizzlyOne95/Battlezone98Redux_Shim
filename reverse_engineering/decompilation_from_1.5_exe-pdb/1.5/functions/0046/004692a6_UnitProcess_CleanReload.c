/*
 * Entry: 004692a6
 * Name: UnitProcess::CleanReload
 * Namespace: UnitProcess
 * Signature: void CleanReload(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanReload(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
    this->task = (AiTask *)0x0;
  }
  return;
}
