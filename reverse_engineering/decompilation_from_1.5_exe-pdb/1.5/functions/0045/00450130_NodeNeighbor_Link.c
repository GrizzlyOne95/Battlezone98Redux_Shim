/*
 * Entry: 00450130
 * Name: NodeNeighbor::Link
 * Namespace: NodeNeighbor
 * Signature: void Link(Strip * param_1, Strip * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NodeNeighbor::Link(Strip *param_1,Strip *param_2)

{
  NodeNeighbor *pNVar1;
  int iVar2;
  
  if (count == 0) {
    curNode = param_1;
  }
  iVar2 = 0;
  if (0 < count) {
    do {
      pNVar1 = ExpandingArray<NodeNeighbor>::operator[](&neighbors,iVar2);
      if (pNVar1->node == param_2) {
        return;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < count);
  }
  iVar2 = count;
  count = count + 1;
  pNVar1 = ExpandingArray<NodeNeighbor>::operator[](&neighbors,iVar2);
  pNVar1->node = param_2;
  return;
}
