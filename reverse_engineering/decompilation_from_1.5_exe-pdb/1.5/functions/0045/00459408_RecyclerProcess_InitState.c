/*
 * Entry: 00459408
 * Name: RecyclerProcess::InitState
 * Namespace: RecyclerProcess
 * Signature: void InitState(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::InitState(RecyclerProcess *this)

{
  bool bVar1;
  int iVar2;
  FollowTask *this_00;
  SitTask *pSVar3;
  GameObject *pGVar4;
  GotoTask *pGVar5;
  GotoGeyser *pGVar6;
  Recycler *pRVar7;
  
  switch(this->curState) {
  case PICKUP:
  case DEPLOY:
    pSVar3 = operator_new(0x138);
    if (pSVar3 == (SitTask *)0x0) break;
    pGVar6 = (GotoGeyser *)SitTask::SitTask(pSVar3,(Craft *)this->craft);
    goto LAB_00459596;
  case WAIT:
                    /* WARNING: Could not recover jumptable at 0x00459424. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x24))();
    return;
  case GOTO:
    pGVar4 = GameObjectHandle::GetObj(this->whoHandle);
    if (pGVar4 == (GameObject *)0x0) {
      pGVar5 = operator_new(0x150);
      if (pGVar5 != (GotoTask *)0x0) {
        pGVar6 = (GotoGeyser *)GotoTask::GotoTask(pGVar5,(Craft *)this->craft,this->where,true);
        goto LAB_00459596;
      }
    }
    else {
      iVar2 = (**(code **)pGVar4->_padding_)();
      if (*(int *)(iVar2 + 0x20) == 0x4745495a) {
        pGVar6 = operator_new(0x158);
        if (pGVar6 != (GotoGeyser *)0x0) {
          pGVar6 = GotoGeyser::GotoGeyser(pGVar6,(Craft *)this->craft,pGVar4);
          goto LAB_00459596;
        }
      }
      else {
        pGVar5 = operator_new(0x150);
        if (pGVar5 != (GotoTask *)0x0) {
          pRVar7 = this->craft;
          goto LAB_004594a2;
        }
      }
    }
    break;
  case FOLLOW:
    pGVar4 = GameObjectHandle::GetObj(this->whoHandle);
    this_00 = operator_new(0x138);
    if (this_00 != (FollowTask *)0x0) {
      pGVar6 = (GotoGeyser *)FollowTask::FollowTask(this_00,(Craft *)this->craft,pGVar4);
      goto LAB_00459596;
    }
    break;
  case BUILD:
    pSVar3 = operator_new(0x138);
    if (pSVar3 == (SitTask *)0x0) {
      pSVar3 = (SitTask *)0x0;
    }
    else {
      pSVar3 = SitTask::SitTask(pSVar3,(Craft *)this->craft);
    }
    this->task = (AiTask *)pSVar3;
    bVar1 = Producer::StartBuild((Producer *)this->craft,this->classtobuild);
    if (bVar1) {
      Say((Craft *)this->craft,RELOAD_MSG,0);
      return;
    }
    this->nextState = DEPLOY;
    return;
  case RECYCLE:
    pGVar4 = GetClosestScrapDropoff((GameObject *)this->craft);
    if (pGVar4 == (GameObject *)0x0) {
      this->task = (AiTask *)0x0;
      return;
    }
    pGVar5 = operator_new(0x150);
    if (pGVar5 != (GotoTask *)0x0) {
      pRVar7 = this->craft;
LAB_004594a2:
      pGVar6 = (GotoGeyser *)GotoTask::GotoTask(pGVar5,(Craft *)pRVar7,pGVar4);
      goto LAB_00459596;
    }
    break;
  case GOTO_GEYSER:
    pGVar6 = operator_new(0x158);
    if (pGVar6 != (GotoGeyser *)0x0) {
      pGVar6 = GotoGeyser::GotoGeyser(pGVar6,(Craft *)this->craft);
      goto LAB_00459596;
    }
    break;
  default:
    goto switchD_00459419_default;
  }
  pGVar6 = (GotoGeyser *)0x0;
LAB_00459596:
  this->task = (AiTask *)pGVar6;
switchD_00459419_default:
  return;
}
