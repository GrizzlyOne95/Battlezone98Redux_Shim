/*
 * Entry: 00466a89
 * Name: TugProcess::InitState
 * Namespace: TugProcess
 * Signature: void InitState(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::InitState(TugProcess *this)

{
  FollowTask *this_00;
  TugPickup *pTVar1;
  _OBJ76 *p_Var2;
  GameObject *pGVar3;
  RescueTask *this_01;
  GotoTask *pGVar4;
  
  switch(this->curState) {
  case GOTO:
  case DROPOFF:
    if ((this->where).y != -1e+30) goto LAB_00466ade;
    pGVar4 = operator_new(0x150);
    if (pGVar4 == (GotoTask *)0x0) goto LAB_00466be5;
    pGVar4 = GotoTask::GotoTask(pGVar4,this->craft,(AiPath *)this->craft->_padding_,true);
    break;
  case FOLLOW:
    pGVar3 = GameObjectHandle::GetObj(this->whoHandle);
    this_00 = operator_new(0x138);
    if (this_00 == (FollowTask *)0x0) goto LAB_00466be5;
    pGVar4 = (GotoTask *)FollowTask::FollowTask(this_00,this->craft,pGVar3);
    break;
  case PICKUP:
    pGVar3 = GameObjectHandle::GetObj(this->whoHandle);
    pTVar1 = operator_new(0x160);
    if (pTVar1 == (TugPickup *)0x0) {
      pTVar1 = (TugPickup *)0x0;
    }
    else {
      pTVar1 = TugPickup::TugPickup(pTVar1,this->craft,pGVar3);
    }
    this->task = (AiTask *)pTVar1;
    p_Var2 = (_OBJ76 *)(**(code **)(this->craft->_padding_ + 0x28))();
    this->hitchTug = p_Var2;
    if (pGVar3 != (GameObject *)0x0) {
      p_Var2 = (_OBJ76 *)(**(code **)(pGVar3->_padding_ + 0x28))();
      this->hitchCargo = p_Var2;
      return;
    }
    this->hitchCargo = (_OBJ76 *)0x0;
    return;
  case PARK:
LAB_00466ade:
    pGVar4 = operator_new(0x150);
    if (pGVar4 == (GotoTask *)0x0) {
LAB_00466be5:
      pGVar4 = (GotoTask *)0x0;
    }
    else {
      pGVar4 = GotoTask::GotoTask(pGVar4,this->craft,&this->where);
    }
    break;
  case REPAIR:
    InitRepair(this);
    return;
  case RECYCLE:
    pGVar3 = GetClosestScrapDropoff((GameObject *)this->craft);
    if (pGVar3 == (GameObject *)0x0) {
      this->task = (AiTask *)0x0;
      return;
    }
    pGVar4 = operator_new(0x150);
    if (pGVar4 == (GotoTask *)0x0) goto LAB_00466be5;
    pGVar4 = GotoTask::GotoTask(pGVar4,this->craft,pGVar3);
    break;
  case RESCUE:
    pGVar3 = GameObjectHandle::GetObj(this->whoHandle);
    this_01 = operator_new(0x138);
    if (this_01 == (RescueTask *)0x0) goto LAB_00466be5;
    pGVar4 = (GotoTask *)RescueTask::RescueTask(this_01,this->craft,pGVar3);
    break;
  default:
    goto switchD_00466a9c_default;
  }
  this->task = (AiTask *)pGVar4;
switchD_00466a9c_default:
  return;
}
