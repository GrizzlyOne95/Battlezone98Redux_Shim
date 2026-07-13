/*
 * Entry: 00458dfd
 * Name: RecyclerProcess::ChangesState
 * Namespace: RecyclerProcess
 * Signature: bool ChangesState(RecyclerProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerProcess::ChangesState(RecyclerProcess *this,AiCommand param_1)

{
  bool bVar1;
  UnitMsg UVar2;
  State SVar3;
  
  SVar3 = FOLLOW;
  if ((int)param_1 < 6) {
    if (param_1 != CMD_FOLLOW) {
      if (param_1 != CMD_NONE) {
        if (param_1 != CMD_SELECT) {
          if (param_1 == CMD_STOP) {
            Say((Craft *)this->craft,OTHER_MSG,0);
            bVar1 = Producer::IsBusy((Producer *)this->craft);
            if (bVar1) {
              this->classtobuild = (GameObjectClass *)0x0;
              Producer::CancelBuild((Producer *)this->craft);
            }
            this->nextState = WAIT;
            return true;
          }
          if (param_1 != CMD_GO) {
            return true;
          }
          Say((Craft *)this->craft,GO_MSG,0);
          this->nextState = GOTO;
          return true;
        }
        bVar1 = Producer::IsBusy((Producer *)this->craft);
        if (bVar1) {
          UVar2 = SELECT_USER1_MSG;
        }
        else if (this->curState == GOTO) {
          UVar2 = SELECT_GO_MSG;
        }
        else {
          bVar1 = Producer::CanBuild((Producer *)this->craft);
          if (bVar1) {
            UVar2 = SELECT_WAIT_MSG;
          }
          else {
            UVar2 = SELECT_USER2_MSG;
          }
        }
        Say((Craft *)this->craft,UVar2,0);
        GameObject::GetWhat((GameObject *)this->craft);
      }
      return false;
    }
    UVar2 = FOLLOW_MSG;
  }
  else {
    SVar3 = RECYCLE;
    if (param_1 == CMD_PICKUP) {
      Say((Craft *)this->craft,GO_MSG,0);
      this->nextState = PICKUP;
      return true;
    }
    if (param_1 == CMD_GO_TO_GEYSER) {
      this->nextState = GOTO_GEYSER;
      return true;
    }
    if (param_1 != CMD_RECYCLE) {
      if (param_1 != CMD_BUILD) {
        return true;
      }
      GameObject::GetWhat((GameObject *)this->craft);
      this->classtobuild = (GameObjectClass *)this->craft->_padding_;
      this->nextState = BUILD;
      return true;
    }
    UVar2 = RECYCLE_MSG;
  }
  Say((Craft *)this->craft,UVar2,0);
  this->nextState = SVar3;
  return true;
}
