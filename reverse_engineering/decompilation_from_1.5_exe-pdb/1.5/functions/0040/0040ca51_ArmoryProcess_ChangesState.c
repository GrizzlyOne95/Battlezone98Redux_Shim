/*
 * Entry: 0040ca51
 * Name: ArmoryProcess::ChangesState
 * Namespace: ArmoryProcess
 * Signature: bool ChangesState(ArmoryProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ArmoryProcess::ChangesState(ArmoryProcess *this,AiCommand param_1)

{
  bool bVar1;
  GameObjectClass *pGVar2;
  Armory *this_00;
  UnitMsg UVar3;
  
  if ((int)param_1 < 0xc) {
    if (param_1 == CMD_GET_RELOAD) {
      if ((this->classtobuild != (GameObjectClass *)0x0) &&
         (bVar1 = Producer::IsBusy((Producer *)this->craft), bVar1)) {
        return false;
      }
      Say((Craft *)this->craft,RELOAD_MSG,0);
      pGVar2 = this->craft->reloadItem;
    }
    else {
      if (param_1 == CMD_NONE) {
        return false;
      }
      if (param_1 == CMD_SELECT) {
        bVar1 = Producer::IsBusy((Producer *)this->craft);
        if (bVar1) {
          UVar3 = SELECT_USER1_MSG;
        }
        else if (this->curState == GOTO) {
          UVar3 = SELECT_GO_MSG;
        }
        else {
          bVar1 = Producer::CanBuild((Producer *)this->craft);
          if (bVar1) {
            UVar3 = SELECT_WAIT_MSG;
          }
          else {
            UVar3 = SELECT_USER2_MSG;
          }
        }
        Say((Craft *)this->craft,UVar3,0);
        this_00 = this->craft;
LAB_0040cb77:
        GameObject::GetWhat((GameObject *)this_00);
        return false;
      }
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
      if (param_1 == CMD_GO) {
        Say((Craft *)this->craft,GO_MSG,0);
        this->nextState = GOTO;
        return true;
      }
      if (param_1 == CMD_FOLLOW) {
        Say((Craft *)this->craft,FOLLOW_MSG,0);
        this->nextState = FOLLOW;
        return true;
      }
      if (param_1 == CMD_PICKUP) {
        Say((Craft *)this->craft,GO_MSG,0);
        this->nextState = PICKUP;
        return true;
      }
      if (param_1 != CMD_GET_REPAIR) {
        return true;
      }
      if ((this->classtobuild != (GameObjectClass *)0x0) &&
         (bVar1 = Producer::IsBusy((Producer *)this->craft), bVar1)) {
        return false;
      }
      Say((Craft *)this->craft,KILLED_MSG,0);
      pGVar2 = this->craft->repairItem;
    }
    this->classtobuild = pGVar2;
  }
  else {
    if (param_1 == CMD_GET_WEAPON) {
      UVar3 = RESCUE_MSG;
    }
    else if (param_1 == CMD_GET_CAMERA) {
      UVar3 = USER1_MSG;
    }
    else {
      if (param_1 != CMD_GET_BOMB) {
        if (param_1 == CMD_GO_TO_GEYSER) {
          this->nextState = GOTO_GEYSER;
          return true;
        }
        if (param_1 == CMD_RECYCLE) {
          Say((Craft *)this->craft,RECYCLE_MSG,0);
          this->nextState = RECYCLE;
          return true;
        }
        if (param_1 != CMD_BUILD) {
          return true;
        }
        Say((Craft *)this->craft,SELECT_ATTACK_MSG,0);
        this_00 = this->craft;
        this->classtobuild = (GameObjectClass *)this_00->_padding_;
        if (this_00->_padding_ != 0) {
          this->nextState = LAUNCH;
          return true;
        }
        goto LAB_0040cb77;
      }
      UVar3 = USER2_MSG;
    }
    Say((Craft *)this->craft,UVar3,0);
  }
  this->nextState = LAUNCH;
  return true;
}
