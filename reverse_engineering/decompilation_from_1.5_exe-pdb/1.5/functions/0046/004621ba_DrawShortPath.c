/*
 * Entry: 004621ba
 * Name: DrawShortPath
 * Namespace: Global
 * Signature: void DrawShortPath(PathPlan * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DrawShortPath(PathPlan *param_1)

{
  Node *pNVar1;
  Node *pNVar2;
  int iVar3;
  int iVar4;
  Node **ppNVar5;
  
  WorldRectOutline(ShortPath::Extents::e.x0,ShortPath::Extents::e.z0,ShortPath::Extents::e.x1,
                   ShortPath::Extents::e.z1,0xffffff);
  iVar4 = 0;
  ppNVar5 = ShortPath::Extents::cellNodes;
  if (0 < ShortPath::Extents::dx) {
    do {
      iVar3 = 0;
      if (0 < ShortPath::Extents::dz) {
        do {
          pNVar1 = *ppNVar5;
          ppNVar5 = ppNVar5 + 1;
          if ((pNVar1 != (Node *)0x0) && (pNVar2 = pNVar1->prev, pNVar2 != (Node *)0x0)) {
            WorldLine((pNVar1->pos).x,(pNVar1->pos).z,(pNVar2->pos).x,(pNVar2->pos).z,0xffffff);
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < ShortPath::Extents::dz);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < ShortPath::Extents::dx);
  }
  return;
}
