/*
 * Entry: 0044e600
 * Name: ContainerNeighbor::Link
 * Namespace: ContainerNeighbor
 * Signature: void Link(Strip * param_1, Strip * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ContainerNeighbor::Link(Strip *param_1,Strip *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ContainerNeighbor *pCVar4;
  int iVar5;
  
  iVar5 = maxNeighbors;
  iVar2 = param_1->neighbor;
  while( true ) {
    if (iVar2 == -1) {
      iVar2 = firstFree;
      if (firstFree < 0) {
        if (neighbors == (ContainerNeighbor *)0x0) {
          maxNeighbors = 0x400;
          neighbors = operator_new__(0x4000);
          iVar2 = 0;
          if (0 < maxNeighbors) {
            iVar5 = 0;
            do {
              iVar2 = iVar2 + 1;
              *(int *)((int)&neighbors->next + iVar5) = iVar2;
              iVar5 = iVar5 + 0x10;
            } while (iVar2 < maxNeighbors);
          }
          neighbors[maxNeighbors + -1].next = -1;
          iVar3 = maxNeighbors << 4;
          iVar2 = 0;
        }
        else {
          pathMem = pathMem + maxNeighbors * -0x10;
          uVar1 = maxNeighbors * 2;
          pCVar4 = operator_new__(-(uint)((int)((ulonglong)uVar1 * 0x10 >> 0x20) != 0) |
                                  (uint)((ulonglong)uVar1 * 0x10));
          memcpy(pCVar4,neighbors,maxNeighbors << 4);
          operator_delete__(neighbors);
          neighbors = pCVar4;
          if (maxNeighbors < (int)uVar1) {
            iVar3 = maxNeighbors << 4;
            iVar2 = maxNeighbors;
            do {
              iVar2 = iVar2 + 1;
              *(int *)((int)&neighbors->next + iVar3) = iVar2;
              iVar3 = iVar3 + 0x10;
            } while (iVar2 < (int)uVar1);
          }
          iVar3 = iVar5 * 0x20;
          neighbors[iVar5 * 2 + -1].next = firstFree;
          iVar2 = maxNeighbors;
          maxNeighbors = uVar1;
        }
        pathMem = pathMem + iVar3;
      }
      firstFree = neighbors[iVar2].next;
      neighbors[iVar2].container = param_2;
      neighbors[iVar2].seqNo = param_2->seqNo;
      neighbors[iVar2].next = param_1->neighbor;
      param_1->neighbor = iVar2;
      return;
    }
    if (neighbors[iVar2].container == param_2) break;
    iVar2 = neighbors[iVar2].next;
  }
  return;
}
