/*
 * Entry: 0044e790
 * Name: ContainerNeighbor::Unlink
 * Namespace: ContainerNeighbor
 * Signature: void Unlink(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ContainerNeighbor::Unlink(Strip *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1->neighbor;
  if (param_1->neighbor != -2) {
    while (iVar2 = iVar1, iVar2 != -1) {
      iVar1 = neighbors[iVar2].next;
      neighbors[iVar2].next = firstFree;
      firstFree = iVar2;
    }
    param_1->neighbor = -2;
  }
  return;
}
