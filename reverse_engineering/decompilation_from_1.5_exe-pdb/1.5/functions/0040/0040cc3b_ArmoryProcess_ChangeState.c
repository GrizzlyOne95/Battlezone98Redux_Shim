/*
 * Entry: 0040cc3b
 * Name: ArmoryProcess::ChangeState
 * Namespace: ArmoryProcess
 * Signature: void ChangeState(ArmoryProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryProcess::ChangeState(ArmoryProcess *this,AiCommand param_1)

{
  State SVar1;
  Armory *pAVar2;
  
  SVar1 = this->nextState;
  if (SVar1 != PICKUP) {
    if (SVar1 == GOTO) {
      pAVar2 = this->craft;
      this->where = (AiPath *)pAVar2->_padding_;
      this->release = false;
      this->whoHandle = pAVar2->_padding_;
      if (this->curState != DEPLOY) {
        return;
      }
      goto LAB_0040cc5c;
    }
    if (SVar1 == FOLLOW) {
      if (this->curState == DEPLOY) {
        (**(code **)(this->craft->_padding_ + 0x60))();
      }
      this->whoHandle = this->craft->_padding_;
      return;
    }
    if (SVar1 == LAUNCH) {
      this->where = (AiPath *)this->craft->_padding_;
      return;
    }
    if (SVar1 != GOTO_GEYSER) {
      return;
    }
  }
  if (this->curState != DEPLOY) {
    return;
  }
  pAVar2 = this->craft;
LAB_0040cc5c:
  (**(code **)(pAVar2->_padding_ + 0x60))();
  return;
}
