/*
 * Entry: 004691b7
 * Name: UnitProcess::DoAttack
 * Namespace: UnitProcess
 * Signature: void DoAttack(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoAttack(UnitProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    Say(this->me,KILLED_MSG,this->whoHandle);
    if (this->me->_padding_ == CMD_ATTACK) {
      GameObject::ClearCommand((GameObject *)this->me);
    }
    this->nextState = WAIT;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004691f6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
