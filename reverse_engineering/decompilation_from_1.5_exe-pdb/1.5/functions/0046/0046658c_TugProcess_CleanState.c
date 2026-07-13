/*
 * Entry: 0046658c
 * Name: TugProcess::CleanState
 * Namespace: TugProcess
 * Signature: void CleanState(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::CleanState(TugProcess *this)

{
  if (this->curState == REPAIR) {
    CleanRepair(this);
  }
  else if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
    this->task = (AiTask *)0x0;
  }
  GameObject::ClearCommand((GameObject *)this->craft);
  return;
}
