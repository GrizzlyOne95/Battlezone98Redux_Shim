/*
 * Entry: 00468f93
 * Name: UnitProcess::ChangeState
 * Namespace: UnitProcess
 * Signature: void ChangeState(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::ChangeState(UnitProcess *this)

{
  State SVar1;
  Craft *pCVar2;
  
  SVar1 = this->nextState;
  if (SVar1 == GOTO) {
    pCVar2 = this->me;
    this->where = (AiPath *)pCVar2->_padding_;
    this->whoHandle = pCVar2->_padding_;
    this->exact = pCVar2->_padding_ < 2;
  }
  else if (SVar1 == PATROL) {
    this->where = (AiPath *)this->me->_padding_;
  }
  else {
    if (SVar1 != STAGE) {
      if ((6 < (int)SVar1) && ((((int)SVar1 < 9 || (SVar1 == DEFEND)) || (SVar1 == RESCUE)))) {
        this->whoHandle = this->me->_padding_;
      }
      goto LAB_00469011;
    }
    this->where = (AiPath *)this->me->_padding_;
    this->whoHandle = this->me->_padding_;
  }
  this->release = false;
LAB_00469011:
  this->saveState = NO_STATE;
  this->saveWho = 0;
  return;
}
