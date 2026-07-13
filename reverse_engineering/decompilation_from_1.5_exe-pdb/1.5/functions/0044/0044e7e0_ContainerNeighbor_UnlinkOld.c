/*
 * Entry: 0044e7e0
 * Name: ContainerNeighbor::UnlinkOld
 * Namespace: ContainerNeighbor
 * Signature: void UnlinkOld(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ContainerNeighbor::UnlinkOld(Strip *param_1)

{
  int iVar1;
  int iVar2;
  ContainerNeighbor *pCVar3;
  ContainerNeighbor *pCVar4;
  
  iVar1 = param_1->neighbor;
  pCVar3 = (ContainerNeighbor *)&param_1->neighbor;
  while (iVar2 = iVar1, iVar2 != -1) {
    pCVar4 = neighbors + iVar2;
    if (neighbors[iVar2].seqNo == pCVar4->container->seqNo) {
      iVar1 = pCVar4->next;
      pCVar3 = pCVar4;
    }
    else {
      iVar1 = pCVar4->next;
      pCVar3->next = iVar1;
      neighbors[iVar2].next = firstFree;
      firstFree = iVar2;
    }
  }
  return;
}
