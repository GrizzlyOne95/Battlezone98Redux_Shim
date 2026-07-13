/*
 * Entry: 00483e9e
 * Name: MCReallyNukeItem
 * Namespace: Global
 * Signature: void MCReallyNukeItem(MULTICACHE * param_1, cachenode * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MCReallyNukeItem(MULTICACHE *param_1,cachenode *param_2)

{
  cachenode **ppcVar1;
  cachenode *pcVar2;
  int iVar3;
  cachenode *pcVar4;
  
  nCachePurges = nCachePurges + 1;
  num_purges_temp = num_purges_temp + 1;
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if (param_2 == (cachenode *)0x0) {
    return;
  }
  param_2->Lock = 0;
  MCremove_from_purge(param_1,param_2);
  iVar3 = compute_hash(param_2->assetname);
  ppcVar1 = param_1->Cache + iVar3;
  if (param_2 == *ppcVar1) {
    *ppcVar1 = param_2->Next;
LAB_00483f0f:
    free(param_2);
    param_1->CacheSize = param_1->CacheSize + -1;
  }
  else {
    pcVar4 = *ppcVar1;
    if (*ppcVar1 != (cachenode *)0x0) {
      do {
        pcVar2 = pcVar4->Next;
        if ((pcVar2 == (cachenode *)0x0) || (pcVar2 == param_2)) break;
        pcVar4 = pcVar2;
      } while (pcVar2 != (cachenode *)0x0);
      if ((pcVar4 != (cachenode *)0x0) && (pcVar4->Next != (cachenode *)0x0)) {
        pcVar4->Next = pcVar4->Next->Next;
        goto LAB_00483f0f;
      }
    }
    DEBUG_systemWarning("Freeing bad item \"%s\"\n");
    if (param_2 == param_1->PurgeHead) {
      MCRebuildDamagedPurgeList(param_1);
    }
  }
  return;
}
