/*
 * Entry: 00462cec
 * Name: ShortPath::Make
 * Namespace: ShortPath
 * Signature: void Make(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Make(void)

{
  PathPoint *pPVar1;
  Node *pNVar2;
  uint uVar3;
  bool bVar4;
  
  if (curNode == goalNode) {
    uVar3 = 0;
    for (curNode = goalNode; curNode != (Node *)0x0; curNode = curNode->prev) {
      uVar3 = uVar3 + 1;
    }
    bVar4 = uVar3 == 1;
    if (bVar4) {
      uVar3 = 2;
    }
    std::vector<PathPoint,std::allocator<PathPoint>_>::clear(&path->points);
    std::vector<PathPoint,std::allocator<PathPoint>_>::resize(&path->points,uVar3);
    pNVar2 = goalNode;
    if (bVar4) {
      uVar3 = 1;
      pPVar1 = std::vector<PathPoint,std::allocator<PathPoint>_>::operator[](&path->points,1);
      (pPVar1->point).x = start.x;
      (pPVar1->point).z = start.z;
      pNVar2 = goalNode;
    }
    while (curNode = pNVar2, uVar3 != 0) {
      uVar3 = uVar3 - 1;
      pPVar1 = std::vector<PathPoint,std::allocator<PathPoint>_>::operator[](&path->points,uVar3);
      (pPVar1->point).x = (curNode->pos).x;
      (pPVar1->point).z = (curNode->pos).z;
      pNVar2 = curNode->prev;
    }
    path->flags = 0;
    path->curPoint = 0;
    pPVar1 = std::vector<PathPoint,std::allocator<PathPoint>_>::back(&path->points);
    (path->goal).x = (pPVar1->point).x;
    (path->goal).z = (pPVar1->point).z;
    return;
  }
  path->flags = 1;
  path->curPoint = 0;
  return;
}
