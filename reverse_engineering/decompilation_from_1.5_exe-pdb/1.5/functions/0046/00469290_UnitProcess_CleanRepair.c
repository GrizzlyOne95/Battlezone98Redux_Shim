/*
 * Entry: 00469290
 * Name: UnitProcess::CleanRepair
 * Namespace: UnitProcess
 * Signature: void CleanRepair(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanRepair(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
    this->task = (AiTask *)0x0;
  }
  return;
}
