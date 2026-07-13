/*
 * Entry: 004691a1
 * Name: UnitProcess::CleanAttack
 * Namespace: UnitProcess
 * Signature: void CleanAttack(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanAttack(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
  return;
}
