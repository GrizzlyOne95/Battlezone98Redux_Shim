/*
 * Entry: 00461b59
 * Name: ShortPath::Neighbors::Enumerate
 * Namespace: ShortPath::Neighbors
 * Signature: void Enumerate(int * param_1, Node * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Neighbors::Enumerate(int *param_1,Node ***param_2)

{
  Node *pNVar1;
  Cell *pCVar2;
  
  pNVar1 = curNode;
  count = 0;
  pCVar2 = &curNode->cell;
  Make(pCVar2->x + Extents::xDir,(curNode->cell).z);
  Make(pCVar2->x,(pNVar1->cell).z + Extents::zDir);
  Make(pCVar2->x + Extents::xDir,(pNVar1->cell).z + Extents::zDir);
  *param_1 = count;
  *param_2 = neighbors;
  return;
}
