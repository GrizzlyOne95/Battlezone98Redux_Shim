/*
 * Entry: 00483e44
 * Name: MCRebuildDamagedPurgeList
 * Namespace: Global
 * Signature: void MCRebuildDamagedPurgeList(MULTICACHE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCRebuildDamagedPurgeList(MULTICACHE *param_1)

{
  int iVar1;
  cachenode *pcVar2;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  param_1->PurgeHead = (cachenode *)0x0;
  param_1->PurgeTail = (cachenode *)0x0;
  iVar1 = 0;
  do {
    for (pcVar2 = *(cachenode **)(iVar1 + (int)param_1->Cache); pcVar2 != (cachenode *)0x0;
        pcVar2 = pcVar2->Next) {
      if (pcVar2->Lock == 0) {
        pcVar2->Lock = 1;
        add_to_purge(pcVar2);
      }
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x2000);
  return;
}
