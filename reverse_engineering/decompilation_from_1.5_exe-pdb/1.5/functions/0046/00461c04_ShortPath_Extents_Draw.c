/*
 * Entry: 00461c04
 * Name: ShortPath::Extents::Draw
 * Namespace: ShortPath::Extents
 * Signature: void Draw(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Extents::Draw(void)

{
  Node *pNVar1;
  Node *pNVar2;
  int iVar3;
  int iVar4;
  Node **ppNVar5;
  
  WorldRectOutline(e.x0,e.z0,e.x1,e.z1,0xffffff);
  iVar4 = 0;
  ppNVar5 = cellNodes;
  if (0 < dx) {
    do {
      iVar3 = 0;
      if (0 < dz) {
        do {
          pNVar1 = *ppNVar5;
          ppNVar5 = ppNVar5 + 1;
          if ((pNVar1 != (Node *)0x0) && (pNVar2 = pNVar1->prev, pNVar2 != (Node *)0x0)) {
            WorldLine((pNVar1->pos).x,(pNVar1->pos).z,(pNVar2->pos).x,(pNVar2->pos).z,0xffffff);
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < dz);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < dx);
  }
  return;
}
