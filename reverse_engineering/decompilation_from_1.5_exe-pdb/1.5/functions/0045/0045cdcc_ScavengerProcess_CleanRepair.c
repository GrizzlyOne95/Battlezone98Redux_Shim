/*
 * Entry: 0045cdcc
 * Name: ScavengerProcess::CleanRepair
 * Namespace: ScavengerProcess
 * Signature: void CleanRepair(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::CleanRepair(ScavengerProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
    this->task = (AiTask *)0x0;
  }
  return;
}
