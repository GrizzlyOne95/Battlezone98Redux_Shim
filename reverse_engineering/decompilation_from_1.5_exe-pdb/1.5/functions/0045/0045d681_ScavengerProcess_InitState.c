/*
 * Entry: 0045d681
 * Name: ScavengerProcess::InitState
 * Namespace: ScavengerProcess
 * Signature: void InitState(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::InitState(ScavengerProcess *this)

{
  CoastTask *pCVar1;
  SitTask *pSVar2;
  int iVar3;
  FollowTask *this_00;
  RescueTask *this_01;
  float *pfVar4;
  GameObject *pGVar5;
  GotoTask *pGVar6;
  GameObject *unaff_ESI;
  float fVar7;
  
  switch(this->curState) {
  case START:
    if (5.0 < (float)this->craft->_padding_) {
      pCVar1 = operator_new(0x138);
      if (pCVar1 == (CoastTask *)0x0) {
        pCVar1 = (CoastTask *)0x0;
      }
      else {
        pCVar1 = CoastTask::CoastTask(pCVar1,(Craft *)this->craft);
      }
      this->task = (AiTask *)pCVar1;
      fVar7 = Get_Time();
      this->curState = WAIT;
      this->wait_time = fVar7 + 5.0;
      return;
    }
    pGVar6 = (GotoTask *)RecycleTask_Build((GameObject *)this->craft,(GameObject *)0x0);
    this->curState = RECYCLE;
    break;
  case WAIT:
    pSVar2 = operator_new(0x138);
    if (pSVar2 == (SitTask *)0x0) {
      pSVar2 = (SitTask *)0x0;
    }
    else {
      pSVar2 = SitTask::SitTask(pSVar2,(Craft *)this->craft);
    }
    this->task = (AiTask *)pSVar2;
    fVar7 = Get_Time();
    this->wait_time = fVar7 + 5.0;
    return;
  case GOTO:
    pGVar5 = GameObjectHandle::GetObj(this->whoHandle);
    if ((pGVar5 != (GameObject *)0x0) &&
       (iVar3 = (**(code **)pGVar5->_padding_)(), *(int *)(iVar3 + 0x28) == 7)) goto LAB_0045d741;
    if ((this->where).y == -1.0) {
      pGVar6 = operator_new(0x150);
      if (pGVar6 == (GotoTask *)0x0) goto LAB_0045d8ae;
      pGVar6 = GotoTask::GotoTask(pGVar6,(Craft *)this->craft,(AiPath *)this->craft->_padding_,true)
      ;
    }
    else {
      pGVar6 = operator_new(0x150);
      if (pGVar6 == (GotoTask *)0x0) goto LAB_0045d8ae;
      pGVar6 = GotoTask::GotoTask(pGVar6,(Craft *)this->craft,&this->where);
    }
    break;
  case FOLLOW:
    pGVar5 = GameObjectHandle::GetObj(this->whoHandle);
    this_00 = operator_new(0x138);
    if (this_00 == (FollowTask *)0x0) {
LAB_0045d8ae:
      pGVar6 = (GotoTask *)0x0;
    }
    else {
      pGVar6 = (GotoTask *)FollowTask::FollowTask(this_00,(Craft *)this->craft,pGVar5);
    }
    break;
  case RECYCLE:
    fVar7 = Get_Time();
    pGVar5 = (GameObject *)0x0;
    this->wait_time = fVar7 + 10.0;
LAB_0045d741:
    pGVar6 = (GotoTask *)RecycleTask_Build((GameObject *)this->craft,pGVar5);
    break;
  case REPAIR:
    InitRepair(this);
    return;
  case RESCUE:
    pGVar5 = GameObjectHandle::GetObj(this->whoHandle);
    this_01 = operator_new(0x138);
    if (this_01 == (RescueTask *)0x0) goto LAB_0045d8ae;
    pGVar6 = (GotoTask *)RescueTask::RescueTask(this_01,(Craft *)this->craft,pGVar5);
    break;
  case RETREAT:
    pGVar5 = FindBase(unaff_ESI);
    if (pGVar5 == (GameObject *)0x0) {
      this->task = (AiTask *)0x0;
      this->nextState = WAIT;
      return;
    }
    pfVar4 = (float *)(**(code **)(pGVar5->_padding_ + 0xc))();
    (this->where).x = *pfVar4;
    (this->where).y = pfVar4[1];
    (this->where).z = pfVar4[2];
    pGVar6 = operator_new(0x150);
    if (pGVar6 == (GotoTask *)0x0) {
      pGVar6 = (GotoTask *)0x0;
    }
    else {
      pGVar6 = GotoTask::GotoTask(pGVar6,(Craft *)this->craft,&this->where);
    }
    break;
  case CASH_OUT:
    pGVar5 = GetClosestScrapDropoff((GameObject *)this->craft);
    if (pGVar5 == (GameObject *)0x0) {
      this->task = (AiTask *)0x0;
      return;
    }
    pGVar6 = operator_new(0x150);
    if (pGVar6 == (GotoTask *)0x0) goto LAB_0045d8ae;
    pGVar6 = GotoTask::GotoTask(pGVar6,(Craft *)this->craft,pGVar5);
    break;
  default:
    goto switchD_0045d691_default;
  }
  this->task = (AiTask *)pGVar6;
switchD_0045d691_default:
  return;
}
