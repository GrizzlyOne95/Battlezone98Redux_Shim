/*
 * Entry: 004847f3
 * Name: MCFreeCache
 * Namespace: Global
 * Signature: void MCFreeCache(MULTICACHE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCFreeCache(MULTICACHE *param_1)

{
  cachenode *pcVar1;
  cachenode *pcVar2;
  int iVar3;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if (param_1->Cache != (cachenode **)0x0) {
    iVar3 = 0;
    do {
      pcVar2 = *(cachenode **)(iVar3 + (int)param_1->Cache);
      while (pcVar2 != (cachenode *)0x0) {
        pcVar1 = pcVar2->Next;
        MCReallyNukeItem(param_1,pcVar2);
        pcVar2 = pcVar1;
      }
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x2000);
    param_1->CacheSize = 0;
    param_1->PurgeHead = (cachenode *)0x0;
    param_1->PurgeTail = (cachenode *)0x0;
    free(param_1->Cache);
  }
  return;
}
