/*
 * Entry: 00461b02
 * Name: ShortPath::Neighbors::Make
 * Namespace: ShortPath::Neighbors
 * Signature: void Make(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Neighbors::Make(int param_1,int param_2)

{
  int iVar1;
  Node *pNVar2;
  
  if ((((-1 < param_1) && (-1 < param_2)) && (param_1 != Extents::dx)) && (param_2 != Extents::dz))
  {
    pNVar2 = Node::Make(param_1,param_2);
    AssignCost(pNVar2);
    iVar1 = count;
    if (pNVar2->costFactor <= 100.0) {
      count = count + 1;
      neighbors[iVar1] = pNVar2;
    }
  }
  return;
}
