/*
 * Entry: 0046a3b8
 * Name: UnitProcess::DoRecycle
 * Namespace: UnitProcess
 * Signature: void DoRecycle(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoRecycle(UnitProcess *this)

{
  char cVar1;
  GameObject *pGVar2;
  
  if (this->task != (AiTask *)0x0) {
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 != '\0') {
      pGVar2 = GameObjectHandle::GetObj(this->task[2]._padding_);
      if (pGVar2 != (GameObject *)0x0) {
        (**(code **)(this->me->_padding_ + 0x24))();
      }
    }
  }
  if (this->task != (AiTask *)0x0) {
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 == '\0') {
                    /* WARNING: Could not recover jumptable at 0x0046a3fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(this->task->_padding_ + 0x1c))();
      return;
    }
  }
  if (this->me->_padding_ == CMD_RECYCLE) {
    GameObject::ClearCommand((GameObject *)this->me);
  }
  this->nextState = WAIT;
  return;
}
