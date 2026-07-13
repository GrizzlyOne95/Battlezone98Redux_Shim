/*
 * Entry: 0046907a
 * Name: UnitProcess::DoGoto
 * Namespace: UnitProcess
 * Signature: void DoGoto(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoGoto(UnitProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    if (this->release != false) {
      AiPath::Release(this->where);
    }
    if (this->me->_padding_ == CMD_GO) {
      GameObject::ClearCommand((GameObject *)this->me);
    }
    this->nextState = WAIT;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004690b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
