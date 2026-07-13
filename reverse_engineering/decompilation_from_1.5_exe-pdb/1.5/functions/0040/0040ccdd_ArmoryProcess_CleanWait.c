/*
 * Entry: 0040ccdd
 * Name: ArmoryProcess::CleanWait
 * Namespace: ArmoryProcess
 * Signature: void CleanWait(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryProcess::CleanWait(ArmoryProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
