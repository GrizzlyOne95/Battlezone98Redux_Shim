/*
 * Entry: 00469340
 * Name: UnitProcess::CleanRecycle
 * Namespace: UnitProcess
 * Signature: void CleanRecycle(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanRecycle(UnitProcess *this)

{
  if (this->task != (AiTask *)0x0) {
    (**(code **)this->task->_padding_)(1);
    this->task = (AiTask *)0x0;
    if (this->release != false) {
      AiPath::Release(this->where);
    }
  }
  return;
}
