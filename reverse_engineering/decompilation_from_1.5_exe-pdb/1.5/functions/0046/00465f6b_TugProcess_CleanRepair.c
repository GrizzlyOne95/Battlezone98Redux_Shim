/*
 * Entry: 00465f6b
 * Name: TugProcess::CleanRepair
 * Namespace: TugProcess
 * Signature: void CleanRepair(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::CleanRepair(TugProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
    this->task = (AiTask *)0x0;
  }
  return;
}
