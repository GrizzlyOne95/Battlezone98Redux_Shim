/*
 * Entry: 00453380
 * Name: MoveAwayFromEdge
 * Namespace: Global
 * Signature: Strip * MoveAwayFromEdge(Strip * param_1, Strip * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __cdecl MoveAwayFromEdge(Strip *param_1,Strip *param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  Strip *pSVar4;
  int iVar5;
  
  pSVar4 = param_1->prev;
  if (param_2->x1 == param_1->x0) {
    iVar5 = 0;
  }
  else if (param_2->z1 == param_1->z0) {
    iVar5 = 1;
  }
  else {
    iVar5 = 2;
    if (param_2->x0 != param_1->x1) {
      iVar5 = 3;
    }
  }
  if (pSVar4->x1 == param_1->x0) {
    iVar3 = 0;
  }
  else if (pSVar4->z1 == param_1->z0) {
    iVar3 = 1;
  }
  else {
    iVar3 = 2;
    if (pSVar4->x0 != param_1->x1) {
      iVar3 = 3;
    }
  }
  if (iVar3 != iVar5) {
    return param_2;
  }
  fVar1 = param_2->x;
  fVar2 = param_2->z;
  switch(iVar5) {
  case 0:
  case 2:
    break;
  case 1:
  case 3:
    break;
  default:
    pSVar4 = MakeDetourNode(param_1->x,param_1->z,param_1);
    lastIntNextNode = MakeDetourNode(fVar1,fVar2,param_1);
    param_2->prev = lastIntNextNode;
    lastIntNextNode->prev = pSVar4;
    pSVar4->prev = param_1;
    lastIntNode = pSVar4;
    return pSVar4;
  }
                    /* WARNING: Could not recover jumptable at 0x00453457. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pSVar4 = (Strip *)(*(code *)(&PTR_LAB_00453548)[iVar5])();
  return pSVar4;
}
