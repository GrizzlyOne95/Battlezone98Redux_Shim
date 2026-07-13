/*
 * Entry: 0044e9e0
 * Name: NodeNeighbor::Next
 * Namespace: NodeNeighbor
 * Signature: int Next(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl NodeNeighbor::Next(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 1;
  if (count <= iVar1) {
    iVar1 = -1;
  }
  return iVar1;
}
