/*
 * Entry: 0040cd58
 * Name: ArmoryProcess::InitState
 * Namespace: ArmoryProcess
 * Signature: void InitState(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryProcess::InitState(ArmoryProcess *this)

{
  VECTOR_3D *pVVar1;
  AiPath *pAVar2;
  char cVar3;
  SitTask *this_00;
  int iVar4;
  FollowTask *this_01;
  GameObject *pGVar5;
  GotoTask *pGVar6;
  GotoGeyser *pGVar7;
  float fVar8;
  Armory *pAVar9;
  
  switch(this->curState) {
  case START:
    cVar3 = (**(code **)(this->craft->_padding_ + 0x68))();
    this->nextState = (uint)(cVar3 == '\0') * 2 + PICKUP;
  case WAIT:
                    /* WARNING: Could not recover jumptable at 0x0040cd8b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x20))();
    return;
  case PICKUP:
  case DEPLOY:
    this_00 = operator_new(0x138);
    if (this_00 == (SitTask *)0x0) break;
    pGVar7 = (GotoGeyser *)SitTask::SitTask(this_00,(Craft *)this->craft);
    goto LAB_0040cefb;
  case GOTO:
    pGVar5 = GameObjectHandle::GetObj(this->whoHandle);
    if (pGVar5 == (GameObject *)0x0) {
      pGVar6 = operator_new(0x150);
      if (pGVar6 != (GotoTask *)0x0) {
        pGVar7 = (GotoGeyser *)GotoTask::GotoTask(pGVar6,(Craft *)this->craft,this->where,true);
        goto LAB_0040cefb;
      }
    }
    else {
      iVar4 = (**(code **)pGVar5->_padding_)();
      if (*(int *)(iVar4 + 0x20) == 0x4745495a) {
        pGVar7 = operator_new(0x158);
        if (pGVar7 != (GotoGeyser *)0x0) {
          pGVar7 = GotoGeyser::GotoGeyser(pGVar7,(Craft *)this->craft,pGVar5);
          goto LAB_0040cefb;
        }
      }
      else {
        pGVar6 = operator_new(0x150);
        if (pGVar6 != (GotoTask *)0x0) {
          pAVar9 = this->craft;
          goto LAB_0040ce09;
        }
      }
    }
    break;
  case FOLLOW:
    pGVar5 = GameObjectHandle::GetObj(this->whoHandle);
    this_01 = operator_new(0x138);
    if (this_01 != (FollowTask *)0x0) {
      pGVar7 = (GotoGeyser *)FollowTask::FollowTask(this_01,(Craft *)this->craft,pGVar5);
      goto LAB_0040cefb;
    }
    break;
  case LAUNCH:
    pAVar2 = this->where;
    pVVar1 = &this->pos;
    pVVar1->x = pAVar2->points[1].x;
    fVar8 = pAVar2->points[1].z;
    (this->pos).z = fVar8;
    fVar8 = Terrain_FindFloor((double)pVVar1->x,(double)fVar8);
    pAVar9 = this->craft;
    (this->pos).y = fVar8;
    Armory::LaunchItem(pAVar9,this->classtobuild,pVVar1);
    this->classtobuild = (GameObjectClass *)0x0;
    this->nextState = DEPLOY;
    return;
  case RECYCLE:
    pGVar5 = GetClosestScrapDropoff((GameObject *)this->craft);
    if (pGVar5 == (GameObject *)0x0) {
      this->task = (AiTask *)0x0;
      return;
    }
    pGVar6 = operator_new(0x150);
    if (pGVar6 != (GotoTask *)0x0) {
      pAVar9 = this->craft;
LAB_0040ce09:
      pGVar7 = (GotoGeyser *)GotoTask::GotoTask(pGVar6,(Craft *)pAVar9,pGVar5);
      goto LAB_0040cefb;
    }
    break;
  case GOTO_GEYSER:
    pGVar7 = operator_new(0x158);
    if (pGVar7 != (GotoGeyser *)0x0) {
      pGVar7 = GotoGeyser::GotoGeyser(pGVar7,(Craft *)this->craft);
      goto LAB_0040cefb;
    }
    break;
  default:
    goto switchD_0040cd68_default;
  }
  pGVar7 = (GotoGeyser *)0x0;
LAB_0040cefb:
  this->task = (AiTask *)pGVar7;
switchD_0040cd68_default:
  return;
}
