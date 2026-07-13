/*
 * Entry: 00461e00
 * Name: ShortPath::Draw
 * Namespace: ShortPath
 * Signature: void Draw(PathPlan * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Draw(PathPlan *param_1)

{
  Node *pNVar1;
  Node *pNVar2;
  int iVar3;
  int iVar4;
  Node **ppNVar5;
  
  WorldRectOutline(Extents::e.x0,Extents::e.z0,Extents::e.x1,Extents::e.z1,0xffffff);
  iVar4 = 0;
  ppNVar5 = Extents::cellNodes;
  if (0 < Extents::dx) {
    do {
      iVar3 = 0;
      if (0 < Extents::dz) {
        do {
          pNVar1 = *ppNVar5;
          ppNVar5 = ppNVar5 + 1;
          if ((pNVar1 != (Node *)0x0) && (pNVar2 = pNVar1->prev, pNVar2 != (Node *)0x0)) {
            WorldLine((pNVar1->pos).x,(pNVar1->pos).z,(pNVar2->pos).x,(pNVar2->pos).z,0xffffff);
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < Extents::dz);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < Extents::dx);
  }
  return;
}
