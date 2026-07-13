/*
 * Entry: 00454660
 * Name: ContainerNeighbor::First
 * Namespace: ContainerNeighbor
 * Signature: int First(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ContainerNeighbor::First(Strip *param_1)

{
  int iVar1;
  
  iVar1 = param_1->neighbor;
  if (iVar1 == -2) {
    param_1->neighbor = -1;
    LinkLeft(param_1);
    LinkTop(param_1);
    LinkRight(param_1);
    LinkBottom(param_1);
    return param_1->neighbor;
  }
  if (iVar1 != -1) {
    while ((neighbors[iVar1].container)->seqNo == neighbors[iVar1].seqNo) {
      iVar1 = neighbors[iVar1].next;
      if (iVar1 == -1) {
        return param_1->neighbor;
      }
    }
    Unlink(param_1);
    param_1->neighbor = -1;
    LinkLeft(param_1);
    LinkTop(param_1);
    LinkRight(param_1);
    LinkBottom(param_1);
    iVar1 = param_1->neighbor;
  }
  return iVar1;
}
