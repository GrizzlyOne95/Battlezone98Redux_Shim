/*
 * Entry: 004692d2
 * Name: UnitProcess::DoRescue
 * Namespace: UnitProcess
 * Signature: void DoRescue(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoRescue(UnitProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    if (this->me->_padding_ == CMD_RESCUE) {
      GameObject::ClearCommand((GameObject *)this->me);
    }
    this->nextState = WAIT;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00469301. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
