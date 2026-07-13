/*
 * Entry: 00469853
 * Name: UnitProcess::ChangesState
 * Namespace: UnitProcess
 * Signature: bool ChangesState(UnitProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitProcess::ChangesState(UnitProcess *this,AiCommand param_1)

{
  State SVar1;
  char cVar2;
  bool bVar3;
  GameObject *pGVar4;
  Armory *this_00;
  UnitMsg UVar5;
  AiCommand AVar6;
  Craft *pCVar7;
  
  if (10 < (int)param_1) {
    if (param_1 == CMD_GET_RELOAD) {
      if (this->skipSay == false) {
        Say(this->me,RELOAD_MSG,0);
      }
      cVar2 = (**(code **)(this->me->_padding_ + 100))();
      if ((cVar2 != '\0') &&
         (this_00 = (Armory *)Team::GetSlot((Team *)this->me->_padding_,3), this_00 != (Armory *)0x0
         )) {
        bVar3 = Producer::IsBusy((Producer *)this_00);
        if ((bVar3) || (this_00->_padding_ != 0)) goto LAB_00469a05;
        bVar3 = Armory::CanSendReload(this_00);
        if (bVar3) {
          pCVar7 = this->me;
          AVar6 = CMD_GET_RELOAD;
          goto LAB_004699f0;
        }
      }
      this->nextState = RELOAD;
      return true;
    }
    if (param_1 == CMD_DEFEND) {
      Say(this->me,FOLLOW_MSG,0);
      this->nextState = DEFEND;
      return true;
    }
    if (param_1 == CMD_RESCUE) {
      Say(this->me,RESCUE_MSG,0);
      this->nextState = RESCUE;
      return true;
    }
    if (param_1 == CMD_RECYCLE) {
      Say(this->me,RECYCLE_MSG,0);
      this->nextState = RECYCLE;
      return true;
    }
    if (param_1 == CMD_PATROL) {
      Say(this->me,GO_MSG,0);
      this->nextState = PATROL;
      return true;
    }
    if (param_1 == CMD_STAGE) {
      Say(this->me,GO_MSG,0);
      this->nextState = STAGE;
      return true;
    }
LAB_00469933:
    this->nextState = WAIT;
    return true;
  }
  if (param_1 == CMD_GET_REPAIR) {
    if (this->skipSay == false) {
      Say(this->me,REPAIR_MSG,0);
    }
    cVar2 = (**(code **)(this->me->_padding_ + 100))();
    if ((cVar2 != '\0') &&
       (this_00 = (Armory *)Team::GetSlot((Team *)this->me->_padding_,3), this_00 != (Armory *)0x0))
    {
      bVar3 = Producer::IsBusy((Producer *)this_00);
      if ((bVar3) || (this_00->_padding_ != 0)) {
LAB_00469a05:
        this->skipSay = true;
        return false;
      }
      bVar3 = Armory::CanSendRepair(this_00);
      if (bVar3) {
        pCVar7 = this->me;
        AVar6 = CMD_GET_REPAIR;
LAB_004699f0:
        GameObject::SetCommand((GameObject *)this_00,AVar6,(GameObject *)pCVar7);
        this->me->_padding_ = 0;
        this->skipSay = false;
        return false;
      }
    }
    this->nextState = REPAIR;
    return true;
  }
  if (param_1 == CMD_NONE) {
    return false;
  }
  if (param_1 != CMD_SELECT) {
    if (param_1 == CMD_STOP) {
      Say(this->me,OTHER_MSG,0);
    }
    else {
      if (param_1 == CMD_GO) {
        if (this->me->_padding_ == 0) {
          UVar5 = GO_MSG;
        }
        else {
          UVar5 = GO_OBJECT_MSG;
        }
        Say(this->me,UVar5,0);
        this->nextState = GOTO;
        return true;
      }
      if (param_1 == CMD_ATTACK) {
        Say(this->me,ATTACK_MSG,0);
        this->nextState = ATTACK;
        return true;
      }
      if (param_1 == CMD_FOLLOW) {
        pGVar4 = GameObjectHandle::GetObj(this->me->_padding_);
        if (pGVar4 == GameObject::userObject) {
          UVar5 = FOLLOW_ME_MSG;
        }
        else {
          UVar5 = FOLLOW_MSG;
        }
        Say(this->me,UVar5,0);
        this->nextState = FOLLOW;
        return true;
      }
      if (param_1 == CMD_PICKUP) {
        Say(this->me,OTHER_MSG,0);
        this->nextState = PACKUP;
        return true;
      }
    }
    goto LAB_00469933;
  }
  if (this->me->state == DEPLOYING) {
    UVar5 = SELECT_DEPLOY_MSG;
  }
  else {
    SVar1 = this->curState;
    if (SVar1 == WAIT) {
      UVar5 = SELECT_WAIT_MSG;
    }
    else if (SVar1 == GOTO) {
      UVar5 = SELECT_GO_MSG;
    }
    else {
      if (SVar1 != ATTACK) {
        if (SVar1 == FOLLOW) {
          UVar5 = SELECT_FOLLOW_MSG;
          goto LAB_0046997e;
        }
        if (SVar1 != SUBATTACK) {
          UVar5 = SELECT_OTHER_MSG;
          goto LAB_0046997e;
        }
      }
      UVar5 = SELECT_ATTACK_MSG;
    }
  }
LAB_0046997e:
  Say(this->me,UVar5,0);
  GameObject::GetWhat((GameObject *)this->me);
  return false;
}
