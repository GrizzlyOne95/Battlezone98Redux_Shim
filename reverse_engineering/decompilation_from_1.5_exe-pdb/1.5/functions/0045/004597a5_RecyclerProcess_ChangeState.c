/*
 * Entry: 004597a5
 * Name: RecyclerProcess::ChangeState
 * Namespace: RecyclerProcess
 * Signature: void ChangeState(RecyclerProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::ChangeState(RecyclerProcess *this,AiCommand param_1)

{
  State SVar1;
  GameObject *this_00;
  int iVar2;
  Recycler *pRVar3;
  
  SVar1 = this->nextState;
  if (SVar1 != PICKUP) {
    if (SVar1 == GOTO) {
      pRVar3 = this->craft;
      if (pRVar3->_padding_ == 3) {
        this->where = (AiPath *)pRVar3->_padding_;
        this->release = false;
        this->whoHandle = pRVar3->_padding_;
      }
      if (this->curState != DEPLOY) {
        return;
      }
      goto LAB_004597c4;
    }
    if (SVar1 == FOLLOW) {
      if (this->curState == DEPLOY) {
        (**(code **)(this->craft->_padding_ + 0x60))();
      }
      this_00 = GameObject::GetWho((GameObject *)this->craft);
      iVar2 = 0;
      if (this_00 != (GameObject *)0x0) {
        iVar2 = GameObject::GetHandle(this_00);
      }
      this->whoHandle = iVar2;
      return;
    }
    if (SVar1 != GOTO_GEYSER) {
      return;
    }
  }
  if (this->curState != DEPLOY) {
    return;
  }
  pRVar3 = this->craft;
LAB_004597c4:
  (**(code **)(pRVar3->_padding_ + 0x60))();
  return;
}
