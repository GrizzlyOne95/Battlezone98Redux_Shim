/*
 * Entry: 004697d9
 * Name: UnitProcess::Execute
 * Namespace: UnitProcess
 * Signature: void Execute(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::Execute(UnitProcess *this)

{
  char cVar1;
  
  if (this->nextState != NO_STATE) {
    CleanState(this);
    this->curState = this->nextState;
    this->nextState = NO_STATE;
    InitState(this);
  }
  cVar1 = (**(code **)(this->_padding_ + 0x24))(this->me->_padding_);
  if (cVar1 != '\0') {
    CleanState(this);
    GameObject::GetWhat((GameObject *)this->me);
    (**(code **)(this->_padding_ + 0x28))();
    this->curState = this->nextState;
    this->nextState = NO_STATE;
    this->skipSay = false;
    InitState(this);
    if (this->nextState != NO_STATE) {
      return;
    }
  }
  cVar1 = (**(code **)(this->_padding_ + 0x2c))();
  if (cVar1 != '\0') {
    return;
  }
  DoState(this);
  return;
}
