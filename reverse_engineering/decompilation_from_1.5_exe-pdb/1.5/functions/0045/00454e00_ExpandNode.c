/*
 * Entry: 00454e00
 * Name: ExpandNode
 * Namespace: Global
 * Signature: void ExpandNode(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ExpandNode(Strip *param_1)

{
  float fVar1;
  Strip *pSVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  Strip *pSVar6;
  int iVar7;
  ContainerNeighbor *pCVar8;
  
  NodeNeighbor::count = 0;
  pSVar6 = startNode;
  if (param_1->backward == false) {
    pSVar6 = goalNode;
  }
  if (param_1 == pSVar6) {
    NodeNeighbor::Link(param_1,pSVar6);
    return;
  }
  pSVar6 = param_1->prev;
  iVar7 = ContainerNeighbor::First(param_1);
  pCVar8 = ContainerNeighbor::neighbors;
  for (; -1 < iVar7; iVar7 = pCVar8[iVar7].next) {
    pSVar2 = pCVar8[iVar7].container;
    if (pSVar2 != pSVar6) {
      fVar1 = param_1->x;
      fVar3 = pSVar2->x1 - 0.01;
      fVar4 = pSVar2->x0;
      if ((fVar1 < pSVar2->x0) || (fVar4 = fVar1, fVar1 <= fVar3)) {
        fVar3 = fVar4;
      }
      fVar1 = param_1->z;
      fVar4 = pSVar2->z1 - 0.01;
      fVar5 = pSVar2->z0;
      if ((fVar1 < pSVar2->z0) || (fVar5 = fVar1, fVar1 <= fVar4)) {
        fVar4 = fVar5;
      }
      MakeLinkedNode(fVar3,fVar4,param_1,pSVar2);
      pCVar8 = ContainerNeighbor::neighbors;
    }
  }
  return;
}
