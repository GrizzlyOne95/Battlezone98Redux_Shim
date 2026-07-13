/*
 * Entry: 0046920f
 * Name: UnitProcess::DoFollow
 * Namespace: UnitProcess
 * Signature: void DoFollow(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoFollow(UnitProcess *this)

{
  AiCommand AVar1;
  char cVar2;
  
  cVar2 = (**(code **)(this->task->_padding_ + 0x18))();
  if (cVar2 != '\0') {
    AVar1 = this->me->_padding_;
    if ((AVar1 == CMD_FOLLOW) || (AVar1 == CMD_FORMATION)) {
      GameObject::ClearCommand((GameObject *)this->me);
    }
    this->nextState = WAIT;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00469245. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
