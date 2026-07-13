/*
 * Entry: 00450190
 * Name: NodeNeighbor::GetNode
 * Namespace: NodeNeighbor
 * Signature: Strip * GetNode(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip * __cdecl NodeNeighbor::GetNode(int param_1)

{
  NodeNeighbor *pNVar1;
  
  pNVar1 = ExpandingArray<NodeNeighbor>::operator[](&neighbors,param_1);
  return pNVar1->node;
}
