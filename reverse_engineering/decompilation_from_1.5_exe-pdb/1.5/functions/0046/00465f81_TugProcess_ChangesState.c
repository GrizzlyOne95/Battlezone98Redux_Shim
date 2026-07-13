/*
 * Entry: 00465f81
 * Name: TugProcess::ChangesState
 * Namespace: TugProcess
 * Signature: bool ChangesState(TugProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TugProcess::ChangesState(TugProcess *this,AiCommand param_1)

{
  GameObject *pGVar1;
  UnitMsg UVar2;
  
  if ((int)param_1 < 8) {
    if (param_1 != CMD_PICKUP) {
      if (param_1 != CMD_NONE) {
        if (param_1 != CMD_SELECT) {
          if (param_1 == CMD_STOP) {
            Say(this->craft,OTHER_MSG,0);
            this->nextState = WAIT;
            return true;
          }
          if (param_1 != CMD_GO) {
            if (param_1 != CMD_FOLLOW) {
              return true;
            }
            Say(this->craft,FOLLOW_MSG,0);
            this->nextState = FOLLOW;
            return true;
          }
          Say(this->craft,GO_MSG,0);
          this->nextState = GOTO;
          return true;
        }
        pGVar1 = Tug::GetCargo((Tug *)this->craft);
        if (pGVar1 == (GameObject *)0x0) {
          if (this->curState == WAIT) {
            UVar2 = SELECT_WAIT_MSG;
          }
          else if (this->curState == GOTO) {
            UVar2 = SELECT_GO_MSG;
          }
          else {
            UVar2 = SELECT_OTHER_MSG;
          }
        }
        else {
          UVar2 = SELECT_USER1_MSG;
        }
        Say(this->craft,UVar2,0);
        GameObject::GetWhat((GameObject *)this->craft);
      }
      return false;
    }
    Say(this->craft,USER1_MSG,0);
    this->nextState = PICKUP;
  }
  else if (param_1 == CMD_DROPOFF) {
    Say(this->craft,USER2_MSG,0);
    this->nextState = DROPOFF;
  }
  else if (param_1 == CMD_GET_REPAIR) {
    Say(this->craft,REPAIR_MSG,0);
    this->nextState = REPAIR;
  }
  else if (param_1 == CMD_RESCUE) {
    Say(this->craft,RESCUE_MSG,0);
    this->nextState = RESCUE;
  }
  else if (param_1 == CMD_RECYCLE) {
    Say(this->craft,RECYCLE_MSG,0);
    this->nextState = RECYCLE;
  }
  return true;
}
