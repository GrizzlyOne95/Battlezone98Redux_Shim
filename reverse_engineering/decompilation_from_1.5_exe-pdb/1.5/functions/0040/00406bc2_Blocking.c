/*
 * Entry: 00406bc2
 * Name: Blocking
 * Namespace: Global
 * Signature: void Blocking(GameObject * param_1, GameObject * param_2, bool * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blocking(GameObject *param_1,GameObject *param_2,bool *param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  uint uVar5;
  BlockingInfo *pBVar6;
  BlockingInfo *pBVar7;
  float fVar8;
  int local_8;
  
  iVar1 = GameObject::GetHandle(param_1);
  iVar2 = GameObject::GetHandle(param_2);
  pBVar6 = blocks;
  local_8 = 0x28;
  do {
    if ((pBVar6->mover != 0) && (fVar8 = Get_Time(), 1.0 <= fVar8 - pBVar6->lastBlocked)) {
      pBVar7 = pBVar6;
      for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
        pBVar7->mover = 0;
        pBVar7 = (BlockingInfo *)&pBVar7->blocker;
      }
    }
    pBVar6 = pBVar6 + 1;
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  pBVar6 = blocks;
  uVar5 = 0;
  do {
    if (((pBVar6->mover != 0) && (pBVar6->mover == iVar1)) && (pBVar6->blocker == iVar2)) break;
    uVar5 = uVar5 + 1;
    pBVar6 = pBVar6 + 1;
  } while (uVar5 < 0x28);
  if (uVar5 == 0x28) {
    pBVar6 = blocks;
    uVar5 = 0;
    do {
      if (pBVar6->mover == 0) break;
      uVar5 = uVar5 + 1;
      pBVar6 = pBVar6 + 1;
    } while (uVar5 < 0x28);
    if (uVar5 == 0x28) {
      return;
    }
    pBVar6->mover = iVar1;
    pBVar6->timeBlocked = 0.0;
    pBVar6->blocker = iVar2;
    fVar8 = Get_Time();
    pBVar6->lastBlocked = fVar8;
    pfVar3 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
    (pBVar6->startPos).x = *pfVar3;
    (pBVar6->startPos).y = pfVar3[1];
    (pBVar6->startPos).z = pfVar3[2];
  }
  fVar8 = Get_Time();
  pBVar6->timeBlocked = (fVar8 - pBVar6->lastBlocked) + pBVar6->timeBlocked;
  fVar8 = Get_Time();
  pBVar6->lastBlocked = fVar8;
  if (pBVar6->timeBlocked <= 10.0) {
    *param_3 = false;
  }
  else {
    *param_3 = true;
  }
  return;
}
