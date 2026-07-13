/*
 * Entry: 004b22d6
 * Name: add_to_purge
 * Namespace: Global
 * Signature: void add_to_purge(_texcache * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl add_to_purge(_texcache *param_1)

{
  int iVar1;
  _texcache *unaff_ESI;
  
  if ((unaff_ESI->flags & 1) == 0) {
    unaff_ESI->last_purge = purge_tail;
    if (purge_tail != (_texcache *)0x0) {
      purge_tail->next_purge = unaff_ESI;
    }
    if (purge_head == (_texcache *)0x0) {
      purge_head = unaff_ESI;
    }
    purge_tail = unaff_ESI;
    unaff_ESI->flags = unaff_ESI->flags | 1;
    iVar1 = D3D_Is_In_VideoMemory(unaff_ESI->umap);
    if (iVar1 == 1) {
      unaff_ESI->flags = unaff_ESI->flags | 2;
    }
  }
  return;
}
