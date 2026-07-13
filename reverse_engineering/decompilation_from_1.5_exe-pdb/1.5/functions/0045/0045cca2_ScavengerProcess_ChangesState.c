/*
 * Entry: 0045cca2
 * Name: ScavengerProcess::ChangesState
 * Namespace: ScavengerProcess
 * Signature: bool ChangesState(ScavengerProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavengerProcess::ChangesState(ScavengerProcess *this,AiCommand param_1)

{
  RecycleTask_State RVar1;
  UnitMsg UVar2;
  
  if (7 < (int)param_1) {
    if (param_1 == CMD_GET_REPAIR) {
      Say((Craft *)this->craft,REPAIR_MSG,0);
      this->nextState = REPAIR;
      return true;
    }
    if (param_1 == CMD_RESCUE) {
      Say((Craft *)this->craft,RESCUE_MSG,0);
      this->nextState = RESCUE;
      return true;
    }
    if (param_1 == CMD_RECYCLE) {
      Say((Craft *)this->craft,RECYCLE_MSG,0);
      this->nextState = CASH_OUT;
      return true;
    }
    if (param_1 != CMD_SCAVENGE) {
      return true;
    }
    Say((Craft *)this->craft,GO_MSG,0);
    this->nextState = RECYCLE;
    return true;
  }
  if (param_1 == CMD_PICKUP) {
LAB_0045cd4d:
    Say((Craft *)this->craft,GO_MSG,0);
    this->nextState = GOTO;
    return true;
  }
  if (param_1 == CMD_NONE) {
    return false;
  }
  if (param_1 != CMD_SELECT) {
    if (param_1 == CMD_STOP) {
      Say((Craft *)this->craft,OTHER_MSG,0);
      this->nextState = WAIT;
      return true;
    }
    if (param_1 != CMD_GO) {
      if (param_1 != CMD_FOLLOW) {
        return true;
      }
      Say((Craft *)this->craft,FOLLOW_MSG,0);
      this->nextState = FOLLOW;
      return true;
    }
    goto LAB_0045cd4d;
  }
  if (this->curState == GOTO) {
    UVar2 = SELECT_GO_MSG;
    goto LAB_0045cd36;
  }
  if ((this->curState == RECYCLE) && (this->task != (AiTask *)0x0)) {
    RVar1 = RecycleTask_GetState(this->task);
    if (RVar1 == RecycleTask_Pickup) {
      UVar2 = SELECT_PICKUP_MSG;
      goto LAB_0045cd36;
    }
    if (RVar1 == RecycleTask_Dropoff) {
      UVar2 = SELECT_DROPOFF_MSG;
      goto LAB_0045cd36;
    }
  }
  UVar2 = SELECT_OTHER_MSG;
LAB_0045cd36:
  Say((Craft *)this->craft,UVar2,0);
  GameObject::GetWhat((GameObject *)this->craft);
  return false;
}
